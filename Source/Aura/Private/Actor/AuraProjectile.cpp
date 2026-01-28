// Copyright AbraCode


#include "Actor/AuraProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Aura/Aura.h"
#include "Components/PointLightComponent.h"


AAuraProjectile::AAuraProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);
	Sphere->SetCollisionObjectType(ECC_Projectile);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->InitialSpeed = 550.f;
	ProjectileMovement->MaxSpeed = 550.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;


	FireLoopAudio = CreateDefaultSubobject<UAudioComponent>("FireLoopAudio");
	FireLoopAudio->SetupAttachment(RootComponent);
	FireLoopAudio->bAutoActivate = false;
	FireLoopAudio->bIsUISound = false;
	FireLoopAudio->bAllowSpatialization = true;

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	PointLight->SetupAttachment(RootComponent);
	PointLight->AttenuationRadius = 800.0f;  // Ljus-reach
	PointLight->SourceRadius = 50.0f;        // Soft edges
	PointLight->CastShadows = true;          // Skuggor (Lumen)
	PointLight->SetMobility(EComponentMobility::Movable);  // Dynamiskt
	PointLight->SetVisibility(false);
}

void AAuraProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeSpan);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraProjectile::OnSphereOverlap);
	if (FireLoopSound)
	{
		FireLoopAudio->SetSound(FireLoopSound);
		FireLoopAudio->Play();
	}

	if (PointLight)
	{
		PointLight->Intensity = LightIntensity;
		PointLight->LightColor = LightColor.ToFColor(true);
		PointLight->SetVisibility(bUseLight);
	}


}

void AAuraProjectile::Destroyed()
{
	if (!bHit && !HasAuthority())
	{
		if (FireLoopAudio && FireLoopAudio->IsPlaying()) FireLoopAudio->Stop();
		if (PointLight) PointLight->SetVisibility(false);
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation(), FRotator::ZeroRotator);
		bHit = true;
	}
	Super::Destroyed();
}

void AAuraProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!DamageEffectHandle.Data.IsValid() || DamageEffectHandle.Data.Get()->GetContext().GetEffectCauser() == OtherActor) return;
	if (!UAuraAbilitySystemLibrary::IsNotFriend(DamageEffectHandle.Data.Get()->GetContext().GetEffectCauser(), OtherActor))
	{
		return;
	}
	if (!bHit)
	{
		if (FireLoopAudio && FireLoopAudio->IsPlaying()) FireLoopAudio->Stop();
		if (PointLight) PointLight->SetVisibility(false);
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation(), FRotator::ZeroRotator);
		bHit = true;
	}
	
	if (HasAuthority())
	{
		if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			TargetASC->ApplyGameplayEffectSpecToSelf(*DamageEffectHandle.Data.Get());
		}
		
		Destroy();
	}
	else
	{
		bHit = true;
	}
}
