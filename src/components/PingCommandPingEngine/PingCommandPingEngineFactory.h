/*
 * Copyright (C) 2020 Adrian Carpenter
 *
 * This file is part of Pingnoo (https://github.com/nedrysoft/pingnoo)
 *
 * An open-source cross-platform traceroute analyser.
 *
 * Created by Adrian Carpenter on 22/01/2021.
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

#ifndef PINGNOO_COMPONENTS_PINGCOMMANDPINGENGINE_PINGCOMMANDPINGENGINEFACTORY_H
#define PINGNOO_COMPONENTS_PINGCOMMANDPINGENGINE_PINGCOMMANDPINGENGINEFACTORY_H

#include <IInterface.h>
#include <IPingEngineFactory>

#include <memory>

namespace Nedrysoft { namespace PingCommandPingEngine {
    class PingCommandPingEngine;

    /**
     * @brief       Factory class for PingCommandPingEngine
     *
     * @details     The factory class for creating instances of the PingCommandPingEngine type
     */
    class PingCommandPingEngineFactory :
            public Nedrysoft::RouteAnalyser::IPingEngineFactory {

        private:
            Q_OBJECT

            Q_INTERFACES(Nedrysoft::RouteAnalyser::IPingEngineFactory)

        public:
            /**
             * @brief       Constructs an PingCommandPingEngineFactory.
             */
            PingCommandPingEngineFactory();

            /**
             * @brief       Constructs the PingCommandPingEngineFactory.
             */
            ~PingCommandPingEngineFactory();

        public:
            /**
             * @brief       Creates a PingCommandPingEngine instance.
             *
             * @see         Nedrysoft::RouteAnalyser::IPingEngineFactory::createEngine
             *
             * @param[in]   version the IP version of the engine.
             *
             * @returns     the new PingCommandPingEngine instance.
             */
            auto createEngine(Nedrysoft::Core::IPVersion version) -> Nedrysoft::RouteAnalyser::IPingEngine * override;

            /**
             * @brief       Returns the descriptive name of the factory.
             *
             * @returns     the descriptive name of the ping engine.
             */
            auto description() -> QString override;

            /**
             * @brief       Priority of the ping engine.  The priority is 0=lowest, 1=highest.  This allows
             *              the application to provide a default engine per platform.
             *
             * @returns     the priority.
             */
            auto priority() -> double override;

            /**
             * @brief      Returns whether the ping engine is available for use.
             *
             * @note       Under linux, the ICMP ping engine may not be available if raw sockets cannot
             *             be created, so this allows us to disable a ping engine from being used.
             *
             * @returns    true if available; otherwise false.
             */
            auto available() -> bool override;

            /**
             * @brief      Deletes a ping engine that was created by this instance.
             *
             * @note       If the ping engine is still running, this function will stop it.
             *
             * @param[in]  engine the ping engine to be removed.
             *
             * @returns    true if the engine was deleted; otherwise false.
             */
            auto deleteEngine(Nedrysoft::RouteAnalyser::IPingEngine *engine) -> bool override;

        public:
            /**
             * @brief       Saves the configuration to a JSON object.
             *
             * @returns     the JSON configuration.
             */
            auto saveConfiguration() -> QJsonObject override;

            /**
             * @brief       Loads the configuration.
             *
             * @see         Nedrysoft::Core::IConfiguration::loadConfiguration
             *
             * @param[in]   configuration the configuration as JSON object.
             *
             * @returns     true if loaded; otherwise false.
             */
            auto loadConfiguration(QJsonObject configuration) -> bool override;
    };
}}


#endif // PINGNOO_COMPONENTS_PINGCOMMANDPINGENGINE_PINGCOMMANDPINGENGINEFACTORY_H
