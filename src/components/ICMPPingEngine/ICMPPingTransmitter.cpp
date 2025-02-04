/*
 * Copyright (C) 2020 Adrian Carpenter
 *
 * This file is part of Pingnoo (https://github.com/nedrysoft/pingnoo)
 *
 * An open-source cross-platform traceroute analyser.
 *
 * Created by Adrian Carpenter on 27/03/2020.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ICMPPingTransmitter.h"

#include "ICMPPacket/ICMPPacket.h"
#include "ICMPPingEngine.h"
#include "ICMPPingItem.h"
#include "ICMPPingTarget.h"
#include "ICMPSocket/ICMPSocket.h"

#include <QThread>
#include <QtEndian>
#include <cstdint>
#include <spdlog/spdlog.h>

constexpr auto DefaultTransmitInterval = 10000;

//! @cond
uint16_t Nedrysoft::ICMPPingEngine::ICMPPingTransmitter::m_sequenceId = 1;
QMutex Nedrysoft::ICMPPingEngine::ICMPPingTransmitter::m_sequenceMutex;
//! @endcond

Nedrysoft::ICMPPingEngine::ICMPPingTransmitter::ICMPPingTransmitter(Nedrysoft::ICMPPingEngine::ICMPPingEngine *engine) :
        m_interval(DefaultTransmitInterval),
        m_engine(engine),
        m_isRunning(false) {

}

Nedrysoft::ICMPPingEngine::ICMPPingTransmitter::~ICMPPingTransmitter() {
    qDeleteAll(m_targets);
}

void Nedrysoft::ICMPPingEngine::ICMPPingTransmitter::doWork() {
    QElapsedTimer elapsedTimer;
    unsigned long sampleNumber = 0;

    m_isRunning = true;

    m_engine->setEpoch(QDateTime::currentDateTime());

    while (m_isRunning) {
        if (!m_targets.isEmpty()) {
            SPDLOG_TRACE("Preparing ping set to " + m_targets.last()->hostAddress().toString().toStdString());
        }

        elapsedTimer.restart();

        m_targetsMutex.lock();

        for (auto target : m_targets) {
            auto socket = target->socket();

            auto pingItem = new Nedrysoft::ICMPPingEngine::ICMPPingItem();

            m_sequenceMutex.lock();
            uint16_t currentSequenceId = m_sequenceId++;
            m_sequenceMutex.unlock();

            pingItem->setTarget(target);
            pingItem->setId(target->id());
            pingItem->setSequenceId(currentSequenceId);
            pingItem->setSampleNumber(sampleNumber);

            m_engine->addRequest(pingItem);

            auto buffer = Nedrysoft::ICMPPacket::ICMPPacket::pingPacket(
                    target->id(),
                    currentSequenceId,
                    52,
                    target->hostAddress(),
                    static_cast<Nedrysoft::ICMPPacket::IPVersion>(m_engine->version()) );

            auto result = socket->sendto(buffer, target->hostAddress());

            pingItem->startTimer();

            SPDLOG_TRACE(
                    QString("Sent ping to %1 (TTL=%2, Result=%3)")
                    .arg(target->hostAddress().toString())
                    .arg(socket->ttl()).arg(result)
                    .toStdString() );

            if (result != buffer.length()) {
                SPDLOG_ERROR("Unable to send packet to "+target->hostAddress().toString().toStdString());
            }
        }

        m_targetsMutex.unlock();

        auto elapsedTime = elapsedTimer.elapsed();

        if (elapsedTime < m_interval) {
            QThread::msleep(m_interval - elapsedTime);
        }

        sampleNumber++;
    }
}

auto Nedrysoft::ICMPPingEngine::ICMPPingTransmitter::setInterval(int interval) -> bool {
    m_interval = interval;

    return true;
}

auto Nedrysoft::ICMPPingEngine::ICMPPingTransmitter::addTarget(Nedrysoft::ICMPPingEngine::ICMPPingTarget *target) -> void {
    QMutexLocker locker(&m_targetsMutex);

    m_targets.append(target);
}

auto Nedrysoft::ICMPPingEngine::ICMPPingTransmitter::interval() -> int {
    return m_interval;
}