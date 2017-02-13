/****************************************************************************/
/// @file    Manager.cc
/// @author  Mani Amoozadeh <maniam@ucdavis.edu>
/// @author  second author name
/// @date    August 2013
///
/****************************************************************************/
// VENTOS, Vehicular Network Open Simulator; see http:?
// Copyright (C) 2013-2015
/****************************************************************************/
//
// This file is part of VENTOS.
// VENTOS is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#include <rsu/06_Manager.h>

namespace VENTOS {

Define_Module(VENTOS::ApplRSUManager);

ApplRSUManager::~ApplRSUManager()
{

}


void ApplRSUManager::initialize(int stage)
{
    super::initialize(stage);

	if (stage==0)
	{
        // register signal
        Signal_executeEachTS = registerSignal("executeEachTS");
        omnetpp::getSimulation()->getSystemModule()->subscribe("executeEachTS", this);

        Signal_beaconSignaling = registerSignal("beaconSignaling");
        omnetpp::getSimulation()->getSystemModule()->subscribe("beaconSignaling", this);
	}
}


void ApplRSUManager::finish()
{
    super::finish();

    // unsubscribe
    omnetpp::getSimulation()->getSystemModule()->unsubscribe("executeEachTS", this);
    omnetpp::getSimulation()->getSystemModule()->unsubscribe("beaconSignaling", this);
}


void ApplRSUManager::receiveSignal(omnetpp::cComponent *source, omnetpp::simsignal_t signalID, long i, cObject* details)
{
    Enter_Method_Silent();

    if(signalID == Signal_executeEachTS)
    {
        executeEachTimeStep();
    }
}


void ApplRSUManager::receiveSignal(omnetpp::cComponent *source, omnetpp::simsignal_t signalID, cObject *obj, cObject* details)
{
    Enter_Method_Silent();

    if(signalID == Signal_beaconSignaling)
    {
        omnetpp::cMessage* msg = static_cast<omnetpp::cMessage *>(obj);
        if (msg == NULL) return;

        // treat this as a normal msg
        // calling ApplRSU_04_Manager::handleLowerMsg
        handleLowerMsg(msg);
    }
    // pass it up, if we do not know how to handle the signal
    else
        super::receiveSignal(source, signalID, obj, details);
}


void ApplRSUManager::handleSelfMsg(omnetpp::cMessage* msg)
{
    super::handleSelfMsg(msg);
}


void ApplRSUManager::handleLowerMsg(omnetpp::cMessage* msg)
{
    if (msg->getKind() == TYPE_BEACON_VEHICLE)
    {
        BeaconVehicle* wsm = dynamic_cast<BeaconVehicle*>(msg);
        ASSERT(wsm);

        ApplRSUManager::onBeaconVehicle(wsm);
    }
    else if (msg->getKind() == TYPE_BEACON_BICYCLE)
    {
        BeaconBicycle* wsm = dynamic_cast<BeaconBicycle*>(msg);
        ASSERT(wsm);

        ApplRSUManager::onBeaconBicycle(wsm);
    }
    else if (msg->getKind() == TYPE_BEACON_PEDESTRIAN)
    {
        BeaconPedestrian* wsm = dynamic_cast<BeaconPedestrian*>(msg);
        ASSERT(wsm);

        ApplRSUManager::onBeaconPedestrian(wsm);
    }
    else if (msg->getKind() == TYPE_BEACON_RSU)
    {
        BeaconRSU* wsm = dynamic_cast<BeaconRSU*>(msg);
        ASSERT(wsm);

        ApplRSUManager::onBeaconRSU(wsm);
    }
    else if(msg->getKind() == TYPE_LANECHANGE_DATA)
    {
        LaneChangeMsg* wsm = dynamic_cast<LaneChangeMsg*>(msg);
        ASSERT(wsm);

        ApplRSUManager::onLanechange(wsm);
    }

    delete msg;
}


void ApplRSUManager::executeEachTimeStep()
{
    super::executeEachTimeStep();
}


void ApplRSUManager::onBeaconVehicle(BeaconVehicle* wsm)
{
    super::onBeaconVehicle(wsm);
}


void ApplRSUManager::onBeaconBicycle(BeaconBicycle* wsm)
{
    super::onBeaconBicycle(wsm);
}


void ApplRSUManager::onBeaconPedestrian(BeaconPedestrian* wsm)
{
    super::onBeaconPedestrian(wsm);
}


void ApplRSUManager::onBeaconRSU(BeaconRSU* wsm)
{
    super::onBeaconRSU(wsm);
}


void ApplRSUManager::onLanechange(LaneChangeMsg* wsm)
{
    super::onLanechange(wsm);
}

}