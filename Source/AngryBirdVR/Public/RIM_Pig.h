// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RIM_Pig.generated.h"

UCLASS()
class ANGRYBIRDVR_API ARIM_Pig : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARIM_Pig();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere)
	class UBoxComponent* compCollision;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* compMesh;

	UPROPERTY(EditAnywhere)
	class USoundBase* dieSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AAngryBirdVR_GameModeBase* gameMode;
public:
	UPROPERTY()
	class ARIM_Player* player;

public:
	//OnComponentHit
	UFUNCTION()
	void ComponentHitObject(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//Á×À½
	UFUNCTION()
	void Die();

public:
	//ÀÌÆåÆ®
	UPROPERTY(EditAnywhere)
	UParticleSystem* dieEffect;
};
