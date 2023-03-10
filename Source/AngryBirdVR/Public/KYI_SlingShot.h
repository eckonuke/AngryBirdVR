// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KYI_SlingShot.generated.h"

UCLASS()
class ANGRYBIRDVR_API AKYI_SlingShot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKYI_SlingShot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void PredictPath();
	void Fire();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* compBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* compMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* firePos;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AKYI_AngryRed> birdFactory;
};
