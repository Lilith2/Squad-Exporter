namespace Offsets
{
    public struct AActor
    {
        public const uint Damage = 0x0010; // float
    }

        public const uint ShotDirection = 0x0014; // FVector_NetQuantizeNormal
    }

        public const uint HitInfo = 0x0020; // FHitResult
    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    public struct APawn
    {
        public const uint GroupName = 0x0000; // FString
    }

    }

        public const uint bIsCollapsed = 0x0020; // uint8
    }

        public const uint bIsSelected = 0x0020; // uint8
    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    public struct APlayerController
    {
    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    public struct APlayerState
    {
    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    public struct FBodyInstance
    {
        public const uint ObjectType = 0x001e; // ECollisionChannel
    }

        public const uint CollisionEnabled = 0x0020; // ECollisionEnabled
    }

        public const uint SleepFamily = 0x0059; // ESleepFamily
    }

        public const uint DOFMode = 0x005a; // EDOFMode
    }

        public const uint bUseCCD = 0x005b; // uint8
    }

        public const uint bIgnoreAnalyticCollisions = 0x005b; // uint8
    }

        public const uint bNotifyRigidBodyCollision = 0x005b; // uint8
    }

        public const uint bLockTranslation = 0x005b; // uint8
    }

        public const uint bLockRotation = 0x005b; // uint8
    }

        public const uint bLockXTranslation = 0x005b; // uint8
    }

        public const uint bLockYTranslation = 0x005b; // uint8
    }

        public const uint bLockZTranslation = 0x005c; // uint8
    }

        public const uint bLockXRotation = 0x005c; // uint8
    }

        public const uint bLockYRotation = 0x005c; // uint8
    }

        public const uint bLockZRotation = 0x005c; // uint8
    }

        public const uint bOverrideMaxAngularVelocity = 0x005c; // uint8
    }

        public const uint bOverrideMaxDepenetrationVelocity = 0x005c; // uint8
    }

        public const uint bOverrideWalkableSlopeOnInstance = 0x005d; // uint8
    }

        public const uint bInterpolateWhenSubStepping = 0x005d; // uint8
    }

        public const uint CollisionProfileName = 0x006c; // FName
    }

        public const uint PositionSolverIterationCount = 0x0074; // uint8
    }

        public const uint VelocitySolverIterationCount = 0x0075; // uint8
    }

        public const uint CollisionResponses = 0x0078; // FCollisionResponse
    }

        public const uint MaxDepenetrationVelocity = 0x00a8; // float
    }

        public const uint MassInKgOverride = 0x00ac; // float
    }

        public const uint LinearDamping = 0x00b8; // float
    }

        public const uint AngularDamping = 0x00bc; // float
    }

        public const uint CustomDOFPlaneNormal = 0x00c0; // FVector
    }

        public const uint COMNudge = 0x00cc; // FVector
    }

        public const uint MassScale = 0x00d8; // float
    }

        public const uint InertiaTensorScale = 0x00dc; // FVector
    }

        public const uint WalkableSlopeOverride = 0x00f8; // FWalkableSlopeOverride
    }

    }

        public const uint MaxAngularVelocity = 0x0110; // float
    }

        public const uint CustomSleepThresholdMultiplier = 0x0114; // float
    }

        public const uint StabilizationThresholdMultiplier = 0x0118; // float
    }

        public const uint PhysicsBlendWeight = 0x011c; // float
    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    public struct FPlayerStateDataObject
    {
        public const uint Lives = 0x0000; // int32
    }

        public const uint NumKills = 0x0004; // int32
    }

        public const uint NumVehicleKills = 0x0008; // int32
    }

        public const uint NumDeaths = 0x000c; // int32
    }

        public const uint NumWoundeds = 0x0010; // int32
    }

        public const uint NumWounds = 0x0014; // int32
    }

        public const uint NumTeamkills = 0x0018; // int32
    }

        public const uint HealPoints = 0x001c; // float
    }

        public const uint RevivedPoints = 0x0020; // float
    }

        public const uint TeamWorkScore = 0x0024; // float
    }

        public const uint ObjectiveScore = 0x0028; // float
    }

        public const uint CombatScore = 0x002c; // float
    }

        public const uint bAdmin = 0x0030; // bool
    }

        public const uint bDev = 0x0031; // bool
    }

        public const uint bQA = 0x0032; // bool
    }

        public const uint bMember = 0x0033; // bool
    }

        public const uint bCommander = 0x0034; // bool
    }

        public const uint FireTeamIndex = 0x0038; // int32
    }

        public const uint FireTeamPosition = 0x003c; // int32
    }

        public const uint PlayerNamePrefix = 0x0040; // FString
    }

    }

    }

    }

        public const uint ReplicationKey = 0x0070; // int32
    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    public struct FTViewTarget
    {
    }

        public const uint POV = 0x0010; // FMinimalViewInfo
    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    public struct UCameraShakeBase
    {
        public const uint ParameterName = 0x0000; // FName
    }

        public const uint bGetSeedFromInstance = 0x0008; // uint8
    }

        public const uint bInstanceSeedIsIndex = 0x0008; // uint8
    }

        public const uint bResetSeedOnEmitterLooping = 0x0008; // uint8
    }

        public const uint bRandomlySelectSeedArray = 0x0008; // uint8
    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    public struct UGameInstance
    {
        public const uint FixedEV100 = 0x0000; // float
    }

        public const uint bFixed = 0x0004; // bool
    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    public struct ULevel
    {
        public const uint Rotation = 0x0098; // FRotator
    }

        public const uint Distance = 0x00a4; // float
    }

        public const uint Height = 0x00a8; // float
    }

        public const uint bDisableTimeout = 0x00ac; // bool
    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    public struct UPlayer
    {
    }

    }

    }

    }

    }

    }

    }

    }

    }

    public struct UPrimitiveComponent
    {
        public const uint Damage = 0x0010; // float
    }

        public const uint ShotDirection = 0x0014; // FVector_NetQuantizeNormal
    }

        public const uint HitInfo = 0x0020; // FHitResult
    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    public struct USceneComponent
    {
    }

    }

        public const uint AttachedTo = 0x0030; // FName
    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

    }

}
