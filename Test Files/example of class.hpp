// Class Engine.Actor
// 0x0200 (0x0228 - 0x0028)
class AActor : public UObject
{
public:
	struct FActorTickFunction                     PrimaryActorTick;                                  // 0x0028(0x0030)(Edit, DisableEditOnInstance, NativeAccessSpecifierPublic)
	uint8                                         bNetTemporary : 1;                                 // 0x0058(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8                                         bNetStartup : 1;                                   // 0x0058(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8                                         bOnlyRelevantToOwner : 1;                          // 0x0058(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, DisableEditOnInstance, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8                                         bAlwaysRelevant : 1;                               // 0x0058(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, DisableEditOnInstance, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8                                         bReplicateMovement : 1;                            // 0x0058(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, Net, DisableEditOnInstance, RepNotify, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate))
	uint8                                         bHidden : 1;                                       // 0x0058(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, Net, RepNotify, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate))
	uint8                                         bTearOff : 1;                                      // 0x0058(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Net, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate))
	uint8                                         bForceNetAddressable : 1;                          // 0x0058(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate))
	uint8                                         bExchangedRoles : 1;                               // 0x0059(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Transient, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8                                         bNetLoadOnClient : 1;                              // 0x0059(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8                                         bNetUseOwnerRelevancy : 1;                         // 0x0059(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, DisableEditOnInstance, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8                                         bRelevantForNetworkReplays : 1;                    // 0x0059(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8                                         bRelevantForLevelBounds : 1;                       // 0x0059(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8                                         bReplayRewindable : 1;                             // 0x0059(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, DisableEditOnInstance, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8                                         bAllowTickBeforeBeginPlay : 1;                     // 0x0059(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, DisableEditOnInstance, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8                                         bAutoDestroyWhenFinished : 1;                      // 0x0059(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate))
	uint8                                         bCanBeDamaged : 1;                                 // 0x005A(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, Net, SaveGame, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate))
	uint8                                         bBlockInput : 1;                                   // 0x005A(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, DisableEditOnInstance, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8                                         bCollideWhenPlacing : 1;                           // 0x005A(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8                                         bFindCameraComponentWhenViewTarget : 1;            // 0x005A(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8                                         bGenerateOverlapEventsDuringLevelStreaming : 1;    // 0x005A(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8                                         bIgnoresOriginShifting : 1;                        // 0x005A(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8                                         bEnableAutoLODGeneration : 1;                      // 0x005A(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8                                         bIsEditorOnlyActor : 1;                            // 0x005A(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8                                         bActorSeamlessTraveled : 1;                        // 0x005B(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8                                         bReplicates : 1;                                   // 0x005B(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, DisableEditOnInstance, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected))
	uint8                                         bCanBeInCluster : 1;                               // 0x005B(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, NoDestructor, AdvancedDisplay, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected))
	uint8                                         bAllowReceiveTickEventOnDedicatedServer : 1;       // 0x005B(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected))
	uint8                                         BitPad_5B_4 : 4;                                   // 0x005B(0x0001)(Fixing Bit-Field Size For New Byte [ Dumper-7 ])
	uint8                                         BitPad_5C_0 : 3;                                   // 0x005C(0x0001)(Fixing Bit-Field Size Between Bits [ Dumper-7 ])
	uint8                                         bActorEnableCollision : 1;                         // 0x005C(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate))
	uint8                                         bActorIsBeingDestroyed : 1;                        // 0x005C(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Transient, DuplicateTransient, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate))
	EActorUpdateOverlapsMethod                    UpdateOverlapsMethodDuringLevelStreaming;          // 0x005D(0x0001)(Edit, ZeroConstructor, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
	EActorUpdateOverlapsMethod                    DefaultUpdateOverlapsMethodDuringLevelStreaming;   // 0x005E(0x0001)(Edit, ZeroConstructor, Config, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	ENetRole                                      RemoteRole;                                        // 0x005F(0x0001)(Net, ZeroConstructor, Transient, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	struct FRepMovement                           ReplicatedMovement;                                // 0x0060(0x0034)(Edit, Net, DisableEditOnInstance, RepNotify, NoDestructor, AdvancedDisplay, NativeAccessSpecifierPrivate)
	float                                         InitialLifeSpan;                                   // 0x0094(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         CustomTimeDilation;                                // 0x0098(0x0004)(BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_9C[0x4];                                       // 0x009C(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	struct FRepAttachment                         AttachmentReplication;                             // 0x00A0(0x0040)(Net, Transient, RepNotify, NoDestructor, ContainsInstancedReference, NativeAccessSpecifierPrivate)
	class AActor*                                 Owner;                                             // 0x00E0(0x0008)(Net, ZeroConstructor, IsPlainOldData, RepNotify, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	class FName                                   NetDriverName;                                     // 0x00E8(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
	ENetRole                                      Role;                                              // 0x00F0(0x0001)(Net, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	ENetDormancy                                  NetDormancy;                                       // 0x00F1(0x0001)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	ESpawnActorCollisionHandlingMethod            SpawnCollisionHandlingMethod;                      // 0x00F2(0x0001)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	EAutoReceiveInput                             AutoReceiveInput;                                  // 0x00F3(0x0001)(Edit, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32                                         InputPriority;                                     // 0x00F4(0x0004)(Edit, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	class UInputComponent*                        InputComponent;                                    // 0x00F8(0x0008)(ExportObject, ZeroConstructor, InstancedReference, DuplicateTransient, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         NetCullDistanceSquared;                            // 0x0100(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32                                         NetTag;                                            // 0x0104(0x0004)(ZeroConstructor, Transient, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         NetUpdateFrequency;                                // 0x0108(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         MinNetUpdateFrequency;                             // 0x010C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         bUseRelativeNetUpdateFrequency : 1;                // 0x0110(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8                                         bUseOwnerRelativeNetUpdateFrequency : 1;           // 0x0110(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8                                         Pad_111[0x3];                                      // 0x0111(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	float                                         MinRelativeNetUpdateEvaluationFrequency;           // 0x0114(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         NetPriority;                                       // 0x0118(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_11C[0x4];                                      // 0x011C(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	class APawn*                                  Instigator;                                        // 0x0120(0x0008)(BlueprintVisible, Net, ZeroConstructor, IsPlainOldData, RepNotify, NoDestructor, ExposeOnSpawn, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	TArray<class AActor*>                         Children;                                          // 0x0128(0x0010)(ZeroConstructor, Transient, NativeAccessSpecifierPublic)
	class USceneComponent*                        RootComponent;                                     // 0x0138(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, InstancedReference, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
	TArray<class AMatineeActor*>                  ControllingMatineeActors;                          // 0x0140(0x0010)(ZeroConstructor, Transient, Protected, NativeAccessSpecifierProtected)
	uint8                                         Pad_150[0x8];                                      // 0x0150(0x0008)(Fixing Size After Last Property [ Dumper-7 ])
	TArray<class FName>                           Layers;                                            // 0x0158(0x0010)(ZeroConstructor, NativeAccessSpecifierPublic)
	TWeakObjectPtr<class UChildActorComponent>    ParentComponent;                                   // 0x0168(0x0008)(ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	uint8                                         Pad_170[0x8];                                      // 0x0170(0x0008)(Fixing Size After Last Property [ Dumper-7 ])
	TArray<class FName>                           Tags;                                              // 0x0178(0x0010)(Edit, BlueprintVisible, ZeroConstructor, AdvancedDisplay, NativeAccessSpecifierPublic)
	FMulticastSparseDelegateProperty_             OnTakeAnyDamage;                                   // 0x0188(0x0001)(InstancedReference, BlueprintAssignable, NoDestructor, NativeAccessSpecifierPublic)
	FMulticastSparseDelegateProperty_             OnTakePointDamage;                                 // 0x0189(0x0001)(InstancedReference, BlueprintAssignable, NoDestructor, NativeAccessSpecifierPublic)
	FMulticastSparseDelegateProperty_             OnTakeRadialDamage;                                // 0x018A(0x0001)(InstancedReference, BlueprintAssignable, NoDestructor, NativeAccessSpecifierPublic)
	FMulticastSparseDelegateProperty_             OnActorBeginOverlap;                               // 0x018B(0x0001)(InstancedReference, BlueprintAssignable, NoDestructor, NativeAccessSpecifierPublic)
	FMulticastSparseDelegateProperty_             OnActorEndOverlap;                                 // 0x018C(0x0001)(InstancedReference, BlueprintAssignable, NoDestructor, NativeAccessSpecifierPublic)
	FMulticastSparseDelegateProperty_             OnBeginCursorOver;                                 // 0x018D(0x0001)(InstancedReference, BlueprintAssignable, NoDestructor, NativeAccessSpecifierPublic)
	FMulticastSparseDelegateProperty_             OnEndCursorOver;                                   // 0x018E(0x0001)(InstancedReference, BlueprintAssignable, NoDestructor, NativeAccessSpecifierPublic)
	FMulticastSparseDelegateProperty_             OnClicked;                                         // 0x018F(0x0001)(InstancedReference, BlueprintAssignable, NoDestructor, NativeAccessSpecifierPublic)
	FMulticastSparseDelegateProperty_             OnReleased;                                        // 0x0190(0x0001)(InstancedReference, BlueprintAssignable, NoDestructor, NativeAccessSpecifierPublic)
	FMulticastSparseDelegateProperty_             OnInputTouchBegin;                                 // 0x0191(0x0001)(InstancedReference, BlueprintAssignable, NoDestructor, NativeAccessSpecifierPublic)
	FMulticastSparseDelegateProperty_             OnInputTouchEnd;                                   // 0x0192(0x0001)(InstancedReference, BlueprintAssignable, NoDestructor, NativeAccessSpecifierPublic)
	FMulticastSparseDelegateProperty_             OnInputTouchEnter;                                 // 0x0193(0x0001)(InstancedReference, BlueprintAssignable, NoDestructor, NativeAccessSpecifierPublic)
	FMulticastSparseDelegateProperty_             OnInputTouchLeave;                                 // 0x0194(0x0001)(InstancedReference, BlueprintAssignable, NoDestructor, NativeAccessSpecifierPublic)
	FMulticastSparseDelegateProperty_             OnActorHit;                                        // 0x0195(0x0001)(InstancedReference, BlueprintAssignable, NoDestructor, NativeAccessSpecifierPublic)
	FMulticastSparseDelegateProperty_             OnDestroyed;                                       // 0x0196(0x0001)(InstancedReference, BlueprintAssignable, NoDestructor, NativeAccessSpecifierPublic)
	FMulticastSparseDelegateProperty_             OnEndPlay;                                         // 0x0197(0x0001)(InstancedReference, BlueprintAssignable, NoDestructor, NativeAccessSpecifierPublic)
	uint8                                         Pad_198[0x60];                                     // 0x0198(0x0060)(Fixing Size After Last Property [ Dumper-7 ])
	TArray<class UActorComponent*>                InstanceComponents;                                // 0x01F8(0x0010)(ExportObject, ZeroConstructor, ContainsInstancedReference, NativeAccessSpecifierPrivate)
	TArray<class UActorComponent*>                BlueprintCreatedComponents;                        // 0x0208(0x0010)(ExportObject, ZeroConstructor, NonTransactional, ContainsInstancedReference, TextExportTransient, NativeAccessSpecifierPublic)
	uint8                                         Pad_218[0x10];                                     // 0x0218(0x0010)(Fixing Struct Size After Last Property [ Dumper-7 ])

public:
	class UActorComponent* AddComponent(class FName TemplateName, bool bManualAttachment, const struct FTransform& RelativeTransform, const class UObject* ComponentTemplateContext, bool bDeferredFinish);
	class UActorComponent* AddComponentByClass(TSubclassOf<class UActorComponent> Class_0, bool bManualAttachment, const struct FTransform& RelativeTransform, bool bDeferredFinish);
	void AddTickPrerequisiteActor(class AActor* PrerequisiteActor);
	void AddTickPrerequisiteComponent(class UActorComponent* PrerequisiteComponent);
	void DetachRootComponentFromParent(bool bMaintainWorldPosition);
	void DisableInput(class APlayerController* PlayerController);
	void EnableInput(class APlayerController* PlayerController);
	void FinishAddComponent(class UActorComponent* Component, bool bManualAttachment, const struct FTransform& RelativeTransform);
	void FlushNetDormancy();
	void ForceNetUpdate();
	bool GetTickableWhenPaused();
	void K2_AddActorLocalOffset(const struct FVector& DeltaLocation, bool bSweep, struct FHitResult* SweepHitResult, bool bTeleport);
	void K2_AddActorLocalRotation(const struct FRotator& DeltaRotation, bool bSweep, struct FHitResult* SweepHitResult, bool bTeleport);
	void K2_AddActorLocalTransform(const struct FTransform& NewTransform, bool bSweep, struct FHitResult* SweepHitResult, bool bTeleport);
	void K2_AddActorWorldOffset(const struct FVector& DeltaLocation, bool bSweep, struct FHitResult* SweepHitResult, bool bTeleport);
	void K2_AddActorWorldRotation(const struct FRotator& DeltaRotation, bool bSweep, struct FHitResult* SweepHitResult, bool bTeleport);
	void K2_AddActorWorldTransform(const struct FTransform& DeltaTransform, bool bSweep, struct FHitResult* SweepHitResult, bool bTeleport);
	void K2_AddActorWorldTransformKeepScale(const struct FTransform& DeltaTransform, bool bSweep, struct FHitResult* SweepHitResult, bool bTeleport);
	void K2_AttachRootComponentTo(class USceneComponent* InParent, class FName InSocketName, EAttachLocation AttachLocationType, bool bWeldSimulatedBodies);
	void K2_AttachRootComponentToActor(class AActor* InParentActor, class FName InSocketName, EAttachLocation AttachLocationType, bool bWeldSimulatedBodies);
	void K2_AttachToActor(class AActor* ParentActor, class FName SocketName, EAttachmentRule LocationRule, EAttachmentRule RotationRule, EAttachmentRule ScaleRule, bool bWeldSimulatedBodies);
	void K2_AttachToComponent(class USceneComponent* Parent, class FName SocketName, EAttachmentRule LocationRule, EAttachmentRule RotationRule, EAttachmentRule ScaleRule, bool bWeldSimulatedBodies);
	void K2_DestroyActor();
	void K2_DestroyComponent(class UActorComponent* Component);
	void K2_DetachFromActor(EDetachmentRule LocationRule, EDetachmentRule RotationRule, EDetachmentRule ScaleRule);
	void K2_OnBecomeViewTarget(class APlayerController* PC);
	void K2_OnEndViewTarget(class APlayerController* PC);
	void K2_OnReset();
	bool K2_SetActorLocation(const struct FVector& NewLocation, bool bSweep, struct FHitResult* SweepHitResult, bool bTeleport);
	bool K2_SetActorLocationAndRotation(const struct FVector& NewLocation, const struct FRotator& NewRotation, bool bSweep, struct FHitResult* SweepHitResult, bool bTeleport);
	void K2_SetActorRelativeLocation(const struct FVector& NewRelativeLocation, bool bSweep, struct FHitResult* SweepHitResult, bool bTeleport);
	void K2_SetActorRelativeRotation(const struct FRotator& NewRelativeRotation, bool bSweep, struct FHitResult* SweepHitResult, bool bTeleport);
	void K2_SetActorRelativeTransform(const struct FTransform& NewRelativeTransform, bool bSweep, struct FHitResult* SweepHitResult, bool bTeleport);
	bool K2_SetActorRotation(const struct FRotator& NewRotation, bool bTeleportPhysics);
	bool K2_SetActorTransform(const struct FTransform& NewTransform, bool bSweep, struct FHitResult* SweepHitResult, bool bTeleport);
	bool K2_TeleportTo(const struct FVector& DestLocation, const struct FRotator& DestRotation);
	class UMaterialInstanceDynamic* MakeMIDForMaterial(class UMaterialInterface* Parent);
	void MakeNoise(float Loudness, class APawn* NoiseInstigator, const struct FVector& NoiseLocation, float MaxRange, class FName Tag);
	void OnRep_AttachmentReplication();
	void OnRep_bHidden();
	void OnRep_Instigator();
	void OnRep_Owner();
	void OnRep_ReplicatedMovement();
	void OnRep_ReplicateMovement();
	void PrestreamTextures(float Seconds, bool bEnableStreaming, int32 CinematicTextureGroups);
	void ReceiveActorBeginCursorOver();
	void ReceiveActorBeginOverlap(class AActor* OtherActor);
	void ReceiveActorEndCursorOver();
	void ReceiveActorEndOverlap(class AActor* OtherActor);
	void ReceiveActorOnClicked(const struct FKey& ButtonPressed);
	void ReceiveActorOnInputTouchBegin(const ETouchIndex FingerIndex);
	void ReceiveActorOnInputTouchEnd(const ETouchIndex FingerIndex);
	void ReceiveActorOnInputTouchEnter(const ETouchIndex FingerIndex);
	void ReceiveActorOnInputTouchLeave(const ETouchIndex FingerIndex);
	void ReceiveActorOnReleased(const struct FKey& ButtonReleased);
	void ReceiveAnyDamage(float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, class AActor* DamageCauser);
	void ReceiveBeginPlay();
	void ReceiveDestroyed();
	void ReceiveEndPlay(EEndPlayReason EndPlayReason);
	void ReceiveHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, const struct FVector& HitLocation, const struct FVector& HitNormal, const struct FVector& NormalImpulse, const struct FHitResult& Hit);
	void ReceivePointDamage(float Damage, const class UDamageType* DamageType, const struct FVector& HitLocation, const struct FVector& HitNormal, class UPrimitiveComponent* HitComponent, class FName BoneName, const struct FVector& ShotFromDirection, class AController* InstigatedBy, class AActor* DamageCauser, const struct FHitResult& HitInfo);
	void ReceiveRadialDamage(float DamageReceived, const class UDamageType* DamageType, const struct FVector& Origin, const struct FHitResult& HitInfo, class AController* InstigatedBy, class AActor* DamageCauser);
	void ReceiveTick(float DeltaSeconds);
	void RemoveTickPrerequisiteActor(class AActor* PrerequisiteActor);
	void RemoveTickPrerequisiteComponent(class UActorComponent* PrerequisiteComponent);
	void SetActorEnableCollision(bool bNewActorEnableCollision);
	void SetActorHiddenInGame(bool bNewHidden);
	void SetActorRelativeScale3D(const struct FVector& NewRelativeScale);
	void SetActorScale3D(const struct FVector& NewScale3D);
	void SetActorTickEnabled(bool bEnabled);
	void SetActorTickInterval(float TickInterval);
	void SetAutoDestroyWhenFinished(bool bVal);
	void SetLifeSpan(float InLifespan);
	void SetNetDormancy(ENetDormancy NewDormancy);
	void SetOwner(class AActor* NewOwner);
	void SetReplicateMovement(bool bInReplicateMovement);
	void SetReplicates(bool bInReplicates);
	void SetTickableWhenPaused(bool bTickableWhenPaused);
	void SetTickGroup(ETickingGroup NewTickGroup);
	void SnapRootComponentTo(class AActor* InParentActor, class FName InSocketName);
	void TearOff();
	void UserConstructionScript();

	bool ActorHasTag(class FName Tag) const;
	void GetActorBounds(bool bOnlyCollidingComponents, struct FVector* Origin, struct FVector* BoxExtent, bool bIncludeFromChildActors) const;
	bool GetActorEnableCollision() const;
	void GetActorEyesViewPoint(struct FVector* OutLocation, struct FRotator* OutRotation) const;
	struct FVector GetActorForwardVector() const;
	struct FVector GetActorRelativeScale3D() const;
	struct FVector GetActorRightVector() const;
	struct FVector GetActorScale3D() const;
	float GetActorTickInterval() const;
	float GetActorTimeDilation() const;
	struct FVector GetActorUpVector() const;
	void GetAllChildActors(TArray<class AActor*>* ChildActors, bool bIncludeDescendants) const;
	void GetAttachedActors(TArray<class AActor*>* OutActors, bool bResetArray) const;
	class AActor* GetAttachParentActor() const;
	class FName GetAttachParentSocketName() const;
	class UActorComponent* GetComponentByClass(TSubclassOf<class UActorComponent> ComponentClass) const;
	TArray<class UActorComponent*> GetComponentsByInterface(TSubclassOf<class IInterface> Interface) const;
	TArray<class UActorComponent*> GetComponentsByTag(TSubclassOf<class UActorComponent> ComponentClass, class FName Tag) const;
	float GetDistanceTo(const class AActor* OtherActor) const;
	float GetDotProductTo(const class AActor* OtherActor) const;
	float GetGameTimeSinceCreation() const;
	float GetHorizontalDistanceTo(const class AActor* OtherActor) const;
	float GetHorizontalDotProductTo(const class AActor* OtherActor) const;
	float GetInputAxisKeyValue(const struct FKey& InputAxisKey) const;
	float GetInputAxisValue(const class FName InputAxisName) const;
	struct FVector GetInputVectorAxisValue(const struct FKey& InputAxisKey) const;
	class APawn* GetInstigator() const;
	class AController* GetInstigatorController() const;
	float GetLifeSpan() const;
	ENetRole GetLocalRole() const;
	void GetOverlappingActors(TArray<class AActor*>* OverlappingActors, TSubclassOf<class AActor> ClassFilter) const;
	void GetOverlappingComponents(TArray<class UPrimitiveComponent*>* OverlappingComponents) const;
	class AActor* GetOwner() const;
	class AActor* GetParentActor() const;
	class UChildActorComponent* GetParentComponent() const;
	ENetRole GetRemoteRole() const;
	float GetSquaredDistanceTo(const class AActor* OtherActor) const;
	float GetSquaredHorizontalDistanceTo(const class AActor* OtherActor) const;
	const struct FTransform GetTransform() const;
	struct FVector GetVelocity() const;
	float GetVerticalDistanceTo(const class AActor* OtherActor) const;
	bool HasAuthority() const;
	bool IsActorBeingDestroyed() const;
	bool IsActorTickEnabled() const;
	bool IsChildActor() const;
	bool IsOverlappingActor(const class AActor* Other) const;
	struct FVector K2_GetActorLocation() const;
	struct FRotator K2_GetActorRotation() const;
	TArray<class UActorComponent*> K2_GetComponentsByClass(TSubclassOf<class UActorComponent> ComponentClass) const;
	class USceneComponent* K2_GetRootComponent() const;
	bool WasRecentlyRendered(float Tolerance) const;

public:
	static class UClass* StaticClass()
	{
		return StaticClassImpl<"Actor">();
	}
	static class AActor* GetDefaultObj()
	{
		return GetDefaultObjImpl<AActor>();
	}
};
static_assert(alignof(AActor) == 0x000008, "Wrong alignment on AActor");
static_assert(sizeof(AActor) == 0x000228, "Wrong size on AActor");
static_assert(offsetof(AActor, PrimaryActorTick) == 0x000028, "Member 'AActor::PrimaryActorTick' has a wrong offset!");
static_assert(offsetof(AActor, UpdateOverlapsMethodDuringLevelStreaming) == 0x00005D, "Member 'AActor::UpdateOverlapsMethodDuringLevelStreaming' has a wrong offset!");
static_assert(offsetof(AActor, DefaultUpdateOverlapsMethodDuringLevelStreaming) == 0x00005E, "Member 'AActor::DefaultUpdateOverlapsMethodDuringLevelStreaming' has a wrong offset!");
static_assert(offsetof(AActor, RemoteRole) == 0x00005F, "Member 'AActor::RemoteRole' has a wrong offset!");
static_assert(offsetof(AActor, ReplicatedMovement) == 0x000060, "Member 'AActor::ReplicatedMovement' has a wrong offset!");
static_assert(offsetof(AActor, InitialLifeSpan) == 0x000094, "Member 'AActor::InitialLifeSpan' has a wrong offset!");
static_assert(offsetof(AActor, CustomTimeDilation) == 0x000098, "Member 'AActor::CustomTimeDilation' has a wrong offset!");
static_assert(offsetof(AActor, AttachmentReplication) == 0x0000A0, "Member 'AActor::AttachmentReplication' has a wrong offset!");
static_assert(offsetof(AActor, Owner) == 0x0000E0, "Member 'AActor::Owner' has a wrong offset!");
static_assert(offsetof(AActor, NetDriverName) == 0x0000E8, "Member 'AActor::NetDriverName' has a wrong offset!");
static_assert(offsetof(AActor, Role) == 0x0000F0, "Member 'AActor::Role' has a wrong offset!");
static_assert(offsetof(AActor, NetDormancy) == 0x0000F1, "Member 'AActor::NetDormancy' has a wrong offset!");
static_assert(offsetof(AActor, SpawnCollisionHandlingMethod) == 0x0000F2, "Member 'AActor::SpawnCollisionHandlingMethod' has a wrong offset!");
static_assert(offsetof(AActor, AutoReceiveInput) == 0x0000F3, "Member 'AActor::AutoReceiveInput' has a wrong offset!");
static_assert(offsetof(AActor, InputPriority) == 0x0000F4, "Member 'AActor::InputPriority' has a wrong offset!");
static_assert(offsetof(AActor, InputComponent) == 0x0000F8, "Member 'AActor::InputComponent' has a wrong offset!");
static_assert(offsetof(AActor, NetCullDistanceSquared) == 0x000100, "Member 'AActor::NetCullDistanceSquared' has a wrong offset!");
static_assert(offsetof(AActor, NetTag) == 0x000104, "Member 'AActor::NetTag' has a wrong offset!");
static_assert(offsetof(AActor, NetUpdateFrequency) == 0x000108, "Member 'AActor::NetUpdateFrequency' has a wrong offset!");
static_assert(offsetof(AActor, MinNetUpdateFrequency) == 0x00010C, "Member 'AActor::MinNetUpdateFrequency' has a wrong offset!");
static_assert(offsetof(AActor, MinRelativeNetUpdateEvaluationFrequency) == 0x000114, "Member 'AActor::MinRelativeNetUpdateEvaluationFrequency' has a wrong offset!");
static_assert(offsetof(AActor, NetPriority) == 0x000118, "Member 'AActor::NetPriority' has a wrong offset!");
static_assert(offsetof(AActor, Instigator) == 0x000120, "Member 'AActor::Instigator' has a wrong offset!");
static_assert(offsetof(AActor, Children) == 0x000128, "Member 'AActor::Children' has a wrong offset!");
static_assert(offsetof(AActor, RootComponent) == 0x000138, "Member 'AActor::RootComponent' has a wrong offset!");
static_assert(offsetof(AActor, ControllingMatineeActors) == 0x000140, "Member 'AActor::ControllingMatineeActors' has a wrong offset!");
static_assert(offsetof(AActor, Layers) == 0x000158, "Member 'AActor::Layers' has a wrong offset!");
static_assert(offsetof(AActor, ParentComponent) == 0x000168, "Member 'AActor::ParentComponent' has a wrong offset!");
static_assert(offsetof(AActor, Tags) == 0x000178, "Member 'AActor::Tags' has a wrong offset!");
static_assert(offsetof(AActor, OnTakeAnyDamage) == 0x000188, "Member 'AActor::OnTakeAnyDamage' has a wrong offset!");
static_assert(offsetof(AActor, OnTakePointDamage) == 0x000189, "Member 'AActor::OnTakePointDamage' has a wrong offset!");
static_assert(offsetof(AActor, OnTakeRadialDamage) == 0x00018A, "Member 'AActor::OnTakeRadialDamage' has a wrong offset!");
static_assert(offsetof(AActor, OnActorBeginOverlap) == 0x00018B, "Member 'AActor::OnActorBeginOverlap' has a wrong offset!");
static_assert(offsetof(AActor, OnActorEndOverlap) == 0x00018C, "Member 'AActor::OnActorEndOverlap' has a wrong offset!");
static_assert(offsetof(AActor, OnBeginCursorOver) == 0x00018D, "Member 'AActor::OnBeginCursorOver' has a wrong offset!");
static_assert(offsetof(AActor, OnEndCursorOver) == 0x00018E, "Member 'AActor::OnEndCursorOver' has a wrong offset!");
static_assert(offsetof(AActor, OnClicked) == 0x00018F, "Member 'AActor::OnClicked' has a wrong offset!");
static_assert(offsetof(AActor, OnReleased) == 0x000190, "Member 'AActor::OnReleased' has a wrong offset!");
static_assert(offsetof(AActor, OnInputTouchBegin) == 0x000191, "Member 'AActor::OnInputTouchBegin' has a wrong offset!");
static_assert(offsetof(AActor, OnInputTouchEnd) == 0x000192, "Member 'AActor::OnInputTouchEnd' has a wrong offset!");
static_assert(offsetof(AActor, OnInputTouchEnter) == 0x000193, "Member 'AActor::OnInputTouchEnter' has a wrong offset!");
static_assert(offsetof(AActor, OnInputTouchLeave) == 0x000194, "Member 'AActor::OnInputTouchLeave' has a wrong offset!");
static_assert(offsetof(AActor, OnActorHit) == 0x000195, "Member 'AActor::OnActorHit' has a wrong offset!");
static_assert(offsetof(AActor, OnDestroyed) == 0x000196, "Member 'AActor::OnDestroyed' has a wrong offset!");
static_assert(offsetof(AActor, OnEndPlay) == 0x000197, "Member 'AActor::OnEndPlay' has a wrong offset!");
static_assert(offsetof(AActor, InstanceComponents) == 0x0001F8, "Member 'AActor::InstanceComponents' has a wrong offset!");
static_assert(offsetof(AActor, BlueprintCreatedComponents) == 0x000208, "Member 'AActor::BlueprintCreatedComponents' has a wrong offset!");


// ScriptStruct Squad.SQSwayData
// 0x0094 (0x0094 - 0x0000)
struct FSQSwayData final
{
public:
	struct FSQSwayAspect                          Aspect;                                            // 0x0000(0x000C)(Edit, BlueprintVisible, NoDestructor, NativeAccessSpecifierPublic)
	struct FSQSwayDynamicGroup                    DynamicGroup;                                      // 0x000C(0x0020)(Edit, BlueprintVisible, NoDestructor, NativeAccessSpecifierPublic)
	struct FSQSwayStanceGroup                     StanceGroup;                                       // 0x002C(0x002C)(Edit, BlueprintVisible, NoDestructor, NativeAccessSpecifierPublic)
	float                                         LocationOffsetMultiplier;                          // 0x0058(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	struct FSQSwayLimits                          Limits;                                            // 0x005C(0x0004)(Edit, BlueprintVisible, NoDestructor, NativeAccessSpecifierPublic)
	uint8                                         Pad_60[0x14];                                      // 0x0060(0x0014)(Fixing Size After Last Property [ Dumper-7 ])
	float                                         UnclampedTotalSway;                                // 0x0074(0x0004)(BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         TotalSway;                                         // 0x0078(0x0004)(BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	struct FRotator                               Sway;                                              // 0x007C(0x000C)(BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, NativeAccessSpecifierPublic)
	struct FVector                                LocationOffset;                                    // 0x0088(0x000C)(BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};
static_assert(alignof(FSQSwayData) == 0x000004, "Wrong alignment on FSQSwayData");
static_assert(sizeof(FSQSwayData) == 0x000094, "Wrong size on FSQSwayData");
static_assert(offsetof(FSQSwayData, Aspect) == 0x000000, "Member 'FSQSwayData::Aspect' has a wrong offset!");
static_assert(offsetof(FSQSwayData, DynamicGroup) == 0x00000C, "Member 'FSQSwayData::DynamicGroup' has a wrong offset!");
static_assert(offsetof(FSQSwayData, StanceGroup) == 0x00002C, "Member 'FSQSwayData::StanceGroup' has a wrong offset!");
static_assert(offsetof(FSQSwayData, LocationOffsetMultiplier) == 0x000058, "Member 'FSQSwayData::LocationOffsetMultiplier' has a wrong offset!");
static_assert(offsetof(FSQSwayData, Limits) == 0x00005C, "Member 'FSQSwayData::Limits' has a wrong offset!");
static_assert(offsetof(FSQSwayData, UnclampedTotalSway) == 0x000074, "Member 'FSQSwayData::UnclampedTotalSway' has a wrong offset!");
static_assert(offsetof(FSQSwayData, TotalSway) == 0x000078, "Member 'FSQSwayData::TotalSway' has a wrong offset!");
static_assert(offsetof(FSQSwayData, Sway) == 0x00007C, "Member 'FSQSwayData::Sway' has a wrong offset!");
static_assert(offsetof(FSQSwayData, LocationOffset) == 0x000088, "Member 'FSQSwayData::LocationOffset' has a wrong offset!");