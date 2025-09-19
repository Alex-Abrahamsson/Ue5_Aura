// Copyright AbraCode

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "AuraProjectile.generated.h"

class UNiagaraSystem;
class USphereComponent;
class UProjectileMovementComponent;


UCLASS()
class AURA_API AAuraProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraProjectile();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	FGameplayEffectSpecHandle DamageEffectHandle;

protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;

	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float LifeSpan = 15.f;

	bool bHit = false;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	TObjectPtr<UAudioComponent> FireLoopAudio;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TObjectPtr<USoundBase> FireLoopSound;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TObjectPtr<UNiagaraSystem> ImpactEffect;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TObjectPtr<USoundBase> ImpactSound;
};
