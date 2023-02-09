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
	class USphereComponent* compCollision;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* compMesh;

	bool birdAttack = false;
	bool ObjectAttack = false;
	bool EnemyFall = false;

public:
	UPROPERTY()
	class ARIM_BirdBlue* blue;

	UPROPERTY()
	class AKYI_Wood* wood;

public:
	//조건별로 죽음
	UFUNCTION()
	void Damaged();

	//새
	UFUNCTION()
	void ComponentBeginOverlapBird(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//오브젝트
	//UFUNCTION()
	//void ComponentBeginOverlapObject(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//돼지
 	//UFUNCTION()
 	//void ComponentHitEnemy() //★★★ 코드 필요

	//죽음
	UFUNCTION()
	void Die();




};
