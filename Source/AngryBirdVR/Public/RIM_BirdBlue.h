// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RIM_BirdBlue.generated.h"

UCLASS()
class ANGRYBIRDVR_API ARIM_BirdBlue : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARIM_BirdBlue();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere)
	class USphereComponent* compCollision;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* meshBlue;

	//새(총알) 발사체의 이동. 발사체 형태의 물리 기능을 제고하는 컴포넌트
	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* compMovement;


public:
	//일정 시간 지난 후 새 파괴
	UPROPERTY(EditAnywhere)
	float delayDeathTime = 8.0f;

	//플레이어
	UPROPERTY(EditAnywhere)
	class ARIM_Player* player;

	//
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ARIM_BirdBlue> blueFactory;

public:
	//일정 시간 지난 후 새 파괴
	void Death();

	//파란새 고유 능력
	void BlueBirdSkill();
};
