/*
 * Copyright (C) 2020 Adrian Carpenter
 *
 * This file is part of pingnoo (https://github.com/fizzyade/pingnoo)
 * An open source ping path analyser
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

#ifndef NEDRYSOFT_ROUTEENGINE_ROUTEENGINEFACTORY_H
#define NEDRYSOFT_ROUTEENGINE_ROUTEENGINEFACTORY_H

#include "ComponentSystem/IInterface.h"
#include "Core/IRouteEngineFactory.h"

#include <memory>

namespace Nedrysoft::RouteEngine {
    class RouteEngineFactoryData;

    class RouteEngine;

    /**
     * Factory class for RouteEngine
     *
     * Creates instances of RouteEngine
     *
     */

    class RouteEngineFactory :
            public Nedrysoft::Core::IRouteEngineFactory {

        private:
            Q_OBJECT

            Q_INTERFACES(Nedrysoft::Core::IRouteEngineFactory)

        public:
            RouteEngineFactory();

            ~RouteEngineFactory();

            /**
             * @sa IRouteEngineFactory
             *
             */
            virtual Nedrysoft::Core::IRouteEngine *createEngine();

            virtual QString description();

            /**
             * @sa IConfiguration
             *
             */
            virtual QJsonObject saveConfiguration();

            virtual bool loadConfiguration(QJsonObject configuration);

        protected:
            std::shared_ptr<RouteEngineFactoryData> d;
    };
}


#endif // NEDRYSOFT_ROUTEENGINE_ROUTEENGINEFACTORY_H
