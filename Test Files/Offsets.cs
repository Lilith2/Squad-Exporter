namespace Offsets
{
    public struct AActor
    {
        public const uint Damage = 0x0010; // float
        public const uint ShotDirection = 0x0014; // FVector_NetQuantizeNormal
        public const uint HitInfo = 0x0020; // FHitResult
    }

    public struct ACharacter
    {
    }

    public struct AController
    {
    }

    public struct APawn
    {
        public const uint GroupName = 0x0000; // FString
    }

    public struct APlayerCameraManager
    {
    }

    public struct APlayerController
    {
    }

    public struct APlayerState
    {
    }

    public struct ASQDeployable
    {
    }

    public struct ASQEquipableItem
    {
        public const uint Min = 0x0008; // int64
        public const uint Max = 0x0010; // int64
        public const uint Q1 = 0x0018; // int64
        public const uint Mean = 0x0020; // int64
        public const uint Q3 = 0x0028; // int64
    }

    public struct ASQGameState
    {
        public const uint RS_OnMatchStart = 0x0298; // FMulticastInlineDelegateProperty_
        public const uint bTimerPaused = 0x02a8; // bool
        public const uint bIsTicketBasedGame = 0x02a9; // bool
        public const uint bAllowPublicClientsToRecord = 0x02aa; // bool
        public const uint bTeamPrepsActive = 0x02ab; // bool
        public const uint CurrentLayerInfo = 0x02ac; // FSQLayerSettings
        public const uint OnPlayerJoined = 0x02d0; // FMulticastInlineDelegateProperty_
        public const uint OnPlayerRemoved = 0x02e0; // FMulticastInlineDelegateProperty_
        public const uint AuthorityNumTeams = 0x0328; // int32
        public const uint ChangeTeamWaitTime = 0x032c; // int32
        public const uint WinningTeamTickets = 0x0338; // int32
        public const uint ServerTickRate = 0x033c; // float
        public const uint GameModeName = 0x0340; // FText
        public const uint NextMapName = 0x0368; // FString
        public const uint MaxFireTeamCount = 0x0388; // int32
        public const uint MaxFireTeamSize = 0x038c; // int32
        public const uint MapName = 0x0398; // FText
        public const uint MaxPlayers = 0x03b0; // int32
        public const uint ServerName = 0x03b8; // FString
        public const uint MessageOfTheDay = 0x03c8; // FString
        public const uint TimeOfCompletion = 0x03e0; // float
        public const uint ServerStartTimeStamp = 0x03f8; // int32
        public const uint GlobalSessionId = 0x0408; // FGuid
        public const uint GameFlags = 0x0418; // FSQGameFlags
        public const uint ServerSettings = 0x0430; // FSQServerSettings
    }

    public struct ASQGrenade
    {
        public const uint GrenadeState = 0x0478; // ESQGrenadeState
        public const uint GrenadeConfig = 0x0480; // FSQGrenadeData
        public const uint bCachedOverhandPinpull = 0x04e8; // bool
        public const uint bCachedOverhandThrow = 0x04e9; // bool
        public const uint bCachedUnderhandPinpull = 0x04ea; // bool
        public const uint bCachedUnderhandThrow = 0x04eb; // bool
        public const uint bCachedReloading = 0x04ec; // bool
    }

    public struct ASQPawn
    {
        public const uint bUseEngineActorReplication = 0x0294; // bool
        public const uint bIsUsingNewMovementComponent = 0x0295; // bool
        public const uint Team = 0x0296; // ESQTeam
        public const uint BasedMovement = 0x0298; // FSQBasedMovementInfo
        public const uint BaseTranslationOffset = 0x02d0; // FVector
        public const uint BaseRotationOffset = 0x02e0; // FQuat
        public const uint bInBaseReplication = 0x02f0; // bool
        public const uint OnPawnPossessedEvent = 0x02f8; // FMulticastInlineDelegateProperty_
        public const uint OnPawnUnPossessedEvent = 0x0308; // FMulticastInlineDelegateProperty_
    }

    public struct ASQPlayerCameraManager
    {
        public const uint bDrawStencils = 0x2830; // bool
        public const uint bIgnoreInactiveEffects = 0x2831; // bool
    }

    public struct ASQPlayerState
    {
        public const uint Position = 0x0000; // FVector
        public const uint Damping = 0x000c; // FVector
        public const uint MinLimits = 0x0018; // FVector
        public const uint MaxLimits = 0x0024; // FVector
    }

    public struct ASQSoldier
    {
        public const uint Weight = 0x0008; // float
        public const uint bHasBeenUsed = 0x000c; // bool
    }

    public struct ASQTeamState
    {
    }

    public struct ASQVehicle
    {
        public const uint bForceIfCantPlay = 0x0000; // bool
    }

    public struct ASQVehicleSeat
    {
        public const uint bForceIfCantPlay = 0x0000; // bool
    }

    public struct ASQWeapon
    {
        public const uint bAmmoReductionEnabled = 0x0000; // bool
        public const uint bAffectAllWeapons = 0x0001; // bool
        public const uint AmmoPercentageToLeave = 0x0004; // float
        public const uint bAffectCurrentMagazine = 0x0008; // bool
        public const uint bAffectCurrentMagIfEquipped = 0x0009; // bool
    }

    public struct AWorldSettings
    {
    }

    public struct FBodyInstance
    {
        public const uint ObjectType = 0x001e; // ECollisionChannel
        public const uint CollisionEnabled = 0x0020; // ECollisionEnabled
        public const uint SleepFamily = 0x0059; // ESleepFamily
        public const uint DOFMode = 0x005a; // EDOFMode
        public const uint CollisionProfileName = 0x006c; // FName
        public const uint PositionSolverIterationCount = 0x0074; // uint8
        public const uint VelocitySolverIterationCount = 0x0075; // uint8
        public const uint CollisionResponses = 0x0078; // FCollisionResponse
        public const uint MaxDepenetrationVelocity = 0x00a8; // float
        public const uint MassInKgOverride = 0x00ac; // float
        public const uint LinearDamping = 0x00b8; // float
        public const uint AngularDamping = 0x00bc; // float
        public const uint CustomDOFPlaneNormal = 0x00c0; // FVector
        public const uint COMNudge = 0x00cc; // FVector
        public const uint MassScale = 0x00d8; // float
        public const uint InertiaTensorScale = 0x00dc; // FVector
        public const uint WalkableSlopeOverride = 0x00f8; // FWalkableSlopeOverride
        public const uint MaxAngularVelocity = 0x0110; // float
        public const uint CustomSleepThresholdMultiplier = 0x0114; // float
        public const uint StabilizationThresholdMultiplier = 0x0118; // float
        public const uint PhysicsBlendWeight = 0x011c; // float
    }

    public struct FPlayerStateDataObject
    {
        public const uint Lives = 0x0000; // int32
        public const uint NumKills = 0x0004; // int32
        public const uint NumVehicleKills = 0x0008; // int32
        public const uint NumDeaths = 0x000c; // int32
        public const uint NumWoundeds = 0x0010; // int32
        public const uint NumWounds = 0x0014; // int32
        public const uint NumTeamkills = 0x0018; // int32
        public const uint HealPoints = 0x001c; // float
        public const uint RevivedPoints = 0x0020; // float
        public const uint TeamWorkScore = 0x0024; // float
        public const uint ObjectiveScore = 0x0028; // float
        public const uint CombatScore = 0x002c; // float
        public const uint bAdmin = 0x0030; // bool
        public const uint bDev = 0x0031; // bool
        public const uint bQA = 0x0032; // bool
        public const uint bMember = 0x0033; // bool
        public const uint bCommander = 0x0034; // bool
        public const uint FireTeamIndex = 0x0038; // int32
        public const uint FireTeamPosition = 0x003c; // int32
        public const uint PlayerNamePrefix = 0x0040; // FString
        public const uint ReplicationKey = 0x0070; // int32
    }

    public struct FSQGrenadeData
    {
        public const uint bInfiniteAmmo = 0x0000; // bool
        public const uint InitialAmmo = 0x0004; // int32
        public const uint MaxAmmo = 0x0008; // int32
        public const uint OverhandThrowVelocity = 0x000c; // float
        public const uint UnderhandThrowVelocity = 0x0010; // float
        public const uint ThrowReadyTime = 0x0014; // float
        public const uint OverhandThrowTime = 0x0018; // float
        public const uint UnderhandThrowTime = 0x001c; // float
        public const uint OverhandThrowDuration = 0x0020; // float
        public const uint UnderhandThrowDuration = 0x0024; // float
        public const uint ThrowModeTransitionTime = 0x0028; // float
        public const uint FuseTimeMin = 0x002c; // float
        public const uint FuseTimeMax = 0x0030; // float
        public const uint ReloadTime = 0x0034; // float
        public const uint ProjectileOriginSocketName = 0x0040; // FName
    }

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

    public struct FSQWeaponData
    {
        public const uint bInfiniteAmmo = 0x0000; // bool
        public const uint bInfiniteMags = 0x0001; // bool
        public const uint MaxMags = 0x0004; // int32
        public const uint RoundsPerMag = 0x0008; // int32
        public const uint bAllowRoundInChamber = 0x000c; // bool
        public const uint bAllowSingleLoad = 0x000d; // bool
        public const uint TimeBetweenShots = 0x0020; // float
        public const uint TimeBetweenSingleShots = 0x0024; // float
        public const uint bCanReloadWhenEquipping = 0x0028; // bool
        public const uint bCreateProjectileOnServer = 0x0029; // bool
        public const uint TacticalReloadDuration = 0x002c; // float
        public const uint FinishReloadGracePeriod = 0x0030; // float
        public const uint DryReloadDuration = 0x0034; // float
        public const uint TacticalReloadBipodDuration = 0x0038; // float
        public const uint ReloadDryBipodDuration = 0x003c; // float
        public const uint ADSPostTransitionRatio = 0x0040; // float
        public const uint bAllowZoom = 0x0044; // bool
        public const uint bAverageFireRate = 0x0045; // bool
        public const uint bResetBurstOnTriggerRelease = 0x0046; // bool
        public const uint RoundsBetweenTracer = 0x0050; // int32
        public const uint MuzzleVelocity = 0x0060; // float
        public const uint MaxDamageToApply = 0x0064; // float
        public const uint TimeToStartDamageFallOff = 0x0068; // float
        public const uint DistanceToStartDamageFallOff = 0x006c; // float
        public const uint DamageFallOffRate = 0x0070; // float
        public const uint MinDamageToApply = 0x0074; // float
        public const uint bIsBarrelSocketOnSoldier = 0x0080; // bool
        public const uint BarrelSocketName = 0x0084; // FName
        public const uint MOA = 0x008c; // float
        public const uint MaximumTraceDistance = 0x0098; // float
        public const uint WallHackCheckTraceDistance = 0x009c; // float
        public const uint ProjectileCameraRelativeOffsetMultiplier = 0x00a0; // float
        public const uint bMagMustBeEmptyForVehicleRearm = 0x00a4; // bool
        public const uint bRearmOnlyIfCurrentMagazineIsEmpty = 0x00a5; // bool
        public const uint bRearmCanFillCurrentMagazine = 0x00a6; // bool
        public const uint MinimumTimeBetweenRearms = 0x00a8; // float
        public const uint bRearmOnlyOneMagazine = 0x00ac; // bool
        public const uint bRearmOnlyXRoundsOfAmmo = 0x00ad; // bool
        public const uint RearmRoundsOfAmmoPerRearm = 0x00b0; // int32
        public const uint ArmorPenetrationDepthMillimeters = 0x00b4; // int32
        public const uint TraceDistanceAfterPenetrationMeters = 0x00c0; // float
        public const uint bEmptyMagToReload = 0x00c4; // bool
    }

    public struct FTViewTarget
    {
        public const uint POV = 0x0010; // FMinimalViewInfo
    }

    public struct UCameraModifier_CameraShake
    {
    }

    public struct UCameraShakeBase
    {
        public const uint ParameterName = 0x0000; // FName
    }

    public struct UCharacterMovementComponent
    {
    }

    public struct UGameInstance
    {
        public const uint FixedEV100 = 0x0000; // float
        public const uint bFixed = 0x0004; // bool
    }

    public struct ULevel
    {
        public const uint Rotation = 0x0098; // FRotator
        public const uint Distance = 0x00a4; // float
        public const uint Height = 0x00a8; // float
        public const uint bDisableTimeout = 0x00ac; // bool
    }

    public struct ULocalPlayer
    {
    }

    public struct UMeshComponent
    {
    }

    public struct UPlayer
    {
    }

    public struct UPrimitiveComponent
    {
        public const uint Damage = 0x0010; // float
        public const uint ShotDirection = 0x0014; // FVector_NetQuantizeNormal
        public const uint HitInfo = 0x0020; // FHitResult
    }

    public struct USQAnimInstanceSoldier1P
    {
    }

    public struct USQLayer
    {
        public const uint Status = 0x0000; // FSQAvailabilityState
    }

    public struct USQPawnInventoryComponent
    {
    }

    public struct USQPipScopeCaptureComponent
    {
    }

    public struct USQSoldierMovement
    {
    }

    public struct USQVehicleComponent
    {
    }

    public struct USQVehicleSeatComponent
    {
    }

    public struct USQWeaponStaticInfo
    {
    }

    public struct USceneComponent
    {
        public const uint AttachedTo = 0x0030; // FName
    }

    public struct UWorld
    {
    }

}
