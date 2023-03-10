// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KYI_AngryRed.generated.h"

UCLASS()
class ANGRYBIRDVR_API AKYI_AngryRed : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKYI_AngryRed();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* skeletalMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* sphereComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UProjectileMovementComponent* movement;

	UFUNCTION()
	void ComponentHitObject(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
