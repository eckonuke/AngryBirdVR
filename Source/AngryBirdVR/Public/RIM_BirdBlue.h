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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* compCollision;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//class UStaticMeshComponent* meshBlue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* meshBlue;

	//��(�Ѿ�) �߻�ü�� �̵�. �߻�ü ������ ���� ����� �����ϴ� ������Ʈ
	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* compMovement;


public:
	//���� �ð� ���� �� �� �ı�
	UPROPERTY(EditAnywhere)
	float delayDeathTime = 8.0f;

	//�÷��̾�
	UPROPERTY(EditAnywhere)
	class ARIM_Player* player;


public:
	//���� �ð� ���� �� �� �ı�
	//void Death();


};
