/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/

#include "LmbrCentral_precompiled.h"
#include <AzCore/RTTI/BehaviorContext.h>
#include <LmbrCentral/Shape/ShapeComponentBus.h>

namespace LmbrCentral
{
    // BehaviorConext ShapeComponentNotificationsBus forwarder
    class BehaviorShapeComponentNotificationsBusHandler : public ShapeComponentNotificationsBus::Handler, public AZ::BehaviorEBusHandler
    {
    public:
        AZ_EBUS_BEHAVIOR_BINDER(BehaviorShapeComponentNotificationsBusHandler, "{A82C9481-693B-4010-9812-1A21B106FCC0}", AZ::SystemAllocator,
            OnShapeChanged);

        void OnShapeChanged(ShapeChangeReasons changeReason) override
        {
            Call(FN_OnShapeChanged, changeReason);
        }
    };
    
    void ShapeComponentGeneric::Reflect(AZ::ReflectContext* context)
    {
        AZ::BehaviorContext* behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context);
        if (behaviorContext)
        {
            behaviorContext->EBus<ShapeComponentRequestsBus>("ShapeComponentRequestsBus")
                ->Event("GetShapeType", &ShapeComponentRequestsBus::Events::GetShapeType)
                ->Event("IsPointInside", &ShapeComponentRequestsBus::Events::IsPointInside)
                ->Event("DistanceFromPoint", &ShapeComponentRequestsBus::Events::DistanceFromPoint)
                ->Event("DistanceSquaredFromPoint", &ShapeComponentRequestsBus::Events::DistanceSquaredFromPoint)
                ->Event("GetEncompassingAabb", &ShapeComponentRequestsBus::Events::GetEncompassingAabb)
                ;

            behaviorContext->Enum<(int)ShapeComponentNotifications::ShapeChangeReasons::TransformChanged>("ShapeChangeReasons_TransformChanged")
                           ->Enum<(int)LmbrCentral::ShapeComponentNotifications::ShapeChangeReasons::ShapeChanged>("ShapeChangeReasons_ShapeChanged");
            
            behaviorContext->EBus<ShapeComponentNotificationsBus>("ShapeComponentNotificationsBus")
                ->Handler<BehaviorShapeComponentNotificationsBusHandler>()
                ;
        }
    }
} // namespace LmbrCentral
