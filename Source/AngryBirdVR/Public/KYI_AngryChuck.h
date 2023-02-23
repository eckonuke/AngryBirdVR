// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KYI_AngryChuck.generated.h"

UCLASS()
class ANGRYBIRDVR_API AKYI_AngryChuck : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKYI_AngryChuck();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USkeletalMeshComponent* skeletalMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USphereComponent* sphereComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UProjectileMovementComponent* movement;
	UFUNCTION()
	void ComponentHitObject(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);

	void BirdYellowSkill();

private:
	class ARIM_Player* player;
};
