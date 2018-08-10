<!DOCTYPE CW><CW><customwidgets><customwidget><class>ManipulatedCameraFrame</class>
     <signal> manipulated() </signal>
     <signal> modified() </signal>
     <signal> spinned() </signal>
     <slot access="public"> freezeOrientation(bool) </slot>
     <slot access="public"> setFlySpeed(float) </slot>
     <slot access="public"> setFlyUpVector(Vec &amp;up) </slot>
     <slot access="public"> setRotateAroundCenter(bool) </slot>
     <slot access="public"> setRotationCenter(Vec &amp;center) </slot>
     <slot access="public"> setRotationSensitivity(float) </slot>
     <slot access="public"> setSpinningQuaternion(Quaternion &amp;q) </slot>
     <slot access="public"> setSpinningSensitivity(float) </slot>
     <slot access="public"> setTranslationSensitivity(float) </slot>
     <slot access="public"> setUpdateInterval(int) </slot>
     <slot access="public"> setWheelSensitivity(float) </slot>
     <slot access="public"> startSpinning(int) </slot>
     <slot access="public"> stopSpinning() </slot>
     <slot access="protected"> updateFrame() </slot>
     <slot access="protected"> updateFrameInFlyMode() </slot>
</customwidget></customwidgets></CW>
