// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KYI_Wood.generated.h"

UCLASS()
class ANGRYBIRDVR_API AKYI_Wood : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKYI_Wood();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void ComponentHitObject(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* boxComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* meshComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float life = 3;
	UPROPERTY(EditAnywhere)
		class UParticleSystem* damageEffect;
	UPROPERTY(EditAnywhere)
		class USoundBase* dieSound;

	void Die();

};
