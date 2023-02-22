// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RIM_TNT.generated.h"

UCLASS()
class ANGRYBIRDVR_API ARIM_TNT : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARIM_TNT();

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
	class USkeletalMeshComponent* meshTNT;

	UPROPERTY()
	class AKYI_AngryRed* red;

	UPROPERTY()
	class AKYI_AngryChuck* yellow;

	UPROPERTY()
	class ARIM_BirdBlue* blue;

	UPROPERTY()
	class ARIM_BirdBlack* black;

	UPROPERTY()
	class AKYI_Wood* wood;

	UPROPERTY()
	class AKYI_Glass* glass;

	UPROPERTY()
	class ARIM_Pig* pig;

	UPROPERTY(EditAnywhere)
	class USoundBase* explosionSound;

	bool redBirdAttack = false;
	bool yellowBirdAttack = false;
	bool blueBirdAttack = false;
	bool blackBierdAttack = false;
	bool woodAttack = false;
	bool glassAttack = false;
	bool pigAttack = false;

	UPROPERTY(EditAnywhere)
	float blastRange = 1000.0f;

	UPROPERTY(EditAnywhere)
	float blastRangeDie = 300.0f;

	UPROPERTY(EditAnywhere)
	float ImpulseRange = 1500.0f;


public:
	//새
	//UFUNCTION()
	//void ComponentHitBird(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//오브젝트
	UFUNCTION()
	void ComponentHitObject(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	////폭탄에 범위에 따른 피해. 파괴 또는 충격
	//UFUNCTION()
	//void Shoot();

	//폭탄에 범위에 따른 피해. 파괴 또는 충격
	UFUNCTION()
	void ExplosionDamage();

	//죽음
	UFUNCTION()
	void Die();


};
