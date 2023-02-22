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

	UPROPERTY()
		class AKYI_Wood* wood;

	UPROPERTY()
		class AKYI_Glass* glass;

	UPROPERTY()
		class ARIM_Pig* pig;

	UPROPERTY()
		class ARIM_TNT* tnt;

	UPROPERTY(EditAnywhere)
		float blastRange = 1000.0f;

	UPROPERTY(EditAnywhere)
		float blastRangeDie = 300.0f;

public:
	//���� �ð� ���� �� �� �ı�
	//void Death();

	//��ź�� ������ ���� ����. �ı� �Ǵ� ���
	UFUNCTION()
		void ExplosionDamage();




};
