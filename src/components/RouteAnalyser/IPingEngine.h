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

#ifndef PINGNOO_COMPONENTS_ROUTEANALYSER_IPINGENGINE_H
#define PINGNOO_COMPONENTS_ROUTEANALYSER_IPINGENGINE_H

#include "RouteAnalyserSpec.h"
#include "PingResult.h"

#include <IConfiguration>
#include <IInterface>
#include <QHostAddress>
#include <chrono>

namespace Nedrysoft { namespace RouteAnalyser {
    class IPingTarget;

    /**
     * @brief       The IPingEngine interface describes a ping engine.
     *
     * @details     An engine implements the logic of transmitting, receiving and associating replies to ping requests,
     *              it then signals when a ping result is available.  The underlying mechanism of handling the pings
     *              is hidden from the application.
     *
     * @class       Nedrysoft::RouteAnalyser::IPingEngine IPingEngine.h <IPingEngine>
     */
    class NEDRYSOFT_ROUTEANALYSER_DLLSPEC IPingEngine :
            public Nedrysoft::ComponentSystem::IInterface,
            public Nedrysoft::Core::IConfiguration {

        private:
            Q_OBJECT

            Q_INTERFACES(Nedrysoft::ComponentSystem::IInterface)
            Q_INTERFACES(Nedrysoft::Core::IConfiguration)

        public:
            /**
             * @brief       Destroys the IPingEngine.
             */
            virtual ~IPingEngine() = default;

            /**
             * @brief       Sets the measurement interval for this engine instance.
             *
             * @param[in]   interval the time between successive pings in milliseconds.
             *
             * @returns     returns true on success; otherwise false.
             */
            virtual auto setInterval(int interval) -> bool = 0;

            /**
             * @brief       Returns the interval set on the engine.
             *
             * @returns     the interval between pings in milliseconds.
             */
            virtual auto interval() -> int = 0;

            /**
             * @brief       Sets the reply timeout for this engine instance.
             *
             * @param[in]   timeout the number of milliseconds to wait for a response.
             *
             * @returns     true on success; otherwise false.
             */
            virtual auto setTimeout(int timeout) -> bool = 0;

            /**
             * @brief       Starts ping operations for this engine instance.
             *
             * @returns     true on success; otherwise false.
             */
            virtual auto start() -> bool = 0;

            /**
             * @brief       Stops ping operations for this engine instance.
             *
             * @returns     true on success; otherwise false.
             */
            virtual auto stop() -> bool = 0;

            /**
             * @brief       Adds a ping target to this engine instance.
             *
             * @param[in]   hostAddress the host address of the ping target.
             *
             * @returns     returns a pointer to the created ping target.
             */
            virtual auto addTarget(QHostAddress hostAddress) -> IPingTarget * = 0;

            /**
             * @brief       Adds a ping target to this engine instance.
             *
             * @param[in]   hostAddress the host address of the ping target.
             * @param[in]   ttl the time to live to use.
             *
             * @returns     returns a pointer to the created ping target.
             */
            virtual auto addTarget(QHostAddress hostAddress, int ttl) -> IPingTarget * = 0;

            /**
             * @brief       Transmits a single ping.
             *
             * @note        This is a blocking function.
             *
             * @param[in]   hostAddress the target host address.
             * @param[in]   ttl time to live for this packet.
             * @param[in]   timeout time in seconds to wait for response.
             *
             * @returns     the result of the ping.
             */
            virtual auto singleShot(
                QHostAddress hostAddress,
                int ttl,
                double timeout
            ) -> Nedrysoft::RouteAnalyser::PingResult = 0;

            /**
             * @brief       Removes a ping target from this engine instance.
             *
             * @param[in]   target the ping target to remove.
             *
             * @returns     true on success; otherwise false.
             */
            virtual auto removeTarget(IPingTarget *target) -> bool = 0;

            /**
             * @brief       Gets the epoch for this engine instance.
             *
             * @returns     the time epoch
             */
            virtual auto epoch() -> QDateTime = 0;

            /**
             * @brief       Signal emitted to indicate the state of a ping request.
             *
             * @param[in]   result the result of a ping request.
             */
            Q_SIGNAL void result(Nedrysoft::RouteAnalyser::PingResult result);

            /**
             * @brief       Returns the list of ping targets for the engine.
             *
             * @returns     a QList containing the list of targets.
             */
            virtual auto targets() -> QList<Nedrysoft::RouteAnalyser::IPingTarget *> = 0;
    };
}}

Q_DECLARE_INTERFACE(Nedrysoft::RouteAnalyser::IPingEngine, "com.nedrysoft.routeanalyser.IPingEngine/1.0.0")

#endif // PINGNOO_COMPONENTS_ROUTEANALYSER_IPINGENGINE_H
