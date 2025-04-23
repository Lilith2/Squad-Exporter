namespace Offsets
{
    public struct FSQSwayData
    {
        public const uint Aspect = 0x0000; // FSQSwayAspect
        public const uint DynamicGroup = 0x000c; // FSQSwayDynamicGroup
        public const uint StanceGroup = 0x002c; // FSQSwayStanceGroup
        public const uint LocationOffsetMultiplier = 0x0058; // float
        public const uint Limits = 0x005c; // FSQSwayLimits
        public const uint UnclampedTotalSway = 0x0074; // float
        public const uint TotalSway = 0x0078; // float
        public const uint Sway = 0x007c; // FRotator
        public const uint LocationOffset = 0x0088; // FVector
    }

}
