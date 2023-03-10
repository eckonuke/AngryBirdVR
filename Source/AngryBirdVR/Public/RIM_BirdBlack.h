// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RIM_BirdBlack.generated.h"

UCLASS()
class ANGRYBIRDVR_API ARIM_BirdBlack : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARIM_BirdBlack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USphereComponent* compCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USkeletalMeshComponent* meshBlack;

	//새(총알) 발사체의 이동. 발사체 형태의 물리 기능을 제고하는 컴포넌트
	UPROPERTY(EditAnywhere)
		class UProjectileMovementComponent* compMovement;
	//이펙트
	UPROPERTY(EditAnywhere)
		class UParticleSystem* explodeEffect;
	UPROPERTY(EditAnywhere)
		class USoundBase* explosionSound;
public:
	//일정 시간 지난 후 새 파괴
	UPROPERTY(EditAnywhere)
		float delayDeathTime = 8.0f;

	//플레이어
	UPROPERTY(EditAnywhere)
		class ARIM_Player* player;

	UPROPERTY()
		class AKYI_Wood* wood;

	UPROPERTY()
		class AKYI_Glass* glass;

	UPROPERTY()
		class ARIM_Pig* pig;

	UPROPERTY()
		class ARIM_TNT* tnt;

	UPROPERTY(EditAnywhere)
		float blastRange = 200.0f;

	UPROPERTY(EditAnywhere)
		float blastRangeDie = 150.0f;

public:
	//일정 시간 지난 후 새 파괴
	//void Death();

	//폭탄에 범위에 따른 피해. 파괴 또는 충격
	UFUNCTION()
		void ExplosionDamage();
	UFUNCTION()
		void ComponentHitObject(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
