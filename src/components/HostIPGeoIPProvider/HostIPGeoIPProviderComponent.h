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

#ifndef NEDRYSOFT_HOSTIPGEOIPPROVIDER_HOSTIPGEOIPPROVIDERCOMPONENT_H
#define NEDRYSOFT_HOSTIPGEOIPPROVIDER_HOSTIPGEOIPPROVIDERCOMPONENT_H

#include "ComponentSystem/IComponent.h"
#include "HostIPGeoIPProviderSpec.h"

/**
 * @brief       Namespace for the hostip.com geo ip lookup provider component.
 */
namespace Nedrysoft::HostIPGeoIPProvider {
    class HostIPGeoIPProvider;
}

/**
 * @brief       HostIPGeoIPProviderComponent class
 *
 * @details     Implements a GEO IP lookup provider using hostip.com
 */
class NEDRYSOFT_HOSTIPGEOIPPROVIDER_DLLSPEC HostIPGeoIPProviderComponent :
        public QObject,
        public Nedrysoft::ComponentSystem::IComponent {

    private:
        Q_OBJECT

        Q_PLUGIN_METADATA(IID NedrysoftComponentInterfaceIID FILE "metadata.json")
        Q_INTERFACES(Nedrysoft::ComponentSystem::IComponent)

    public:
        /**
         * @brief   Constructor
         */
        HostIPGeoIPProviderComponent();

        /**
         * @brief Destructor
         *
         */
        ~HostIPGeoIPProviderComponent();

        /**
         * @sa Nedrysoft::ComponentSystem::IComponent
         *
         */
        virtual void initialiseEvent();

    private:

        Nedrysoft::HostIPGeoIPProvider::HostIPGeoIPProvider *m_provider;
};

#endif // NEDRYSOFT_HOSTIPGEOIPPROVIDER_HOSTIPGEOIPPROVIDERCOMPONENT_H
