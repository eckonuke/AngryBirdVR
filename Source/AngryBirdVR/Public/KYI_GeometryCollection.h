// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeometryCollection/GeometryCollectionActor.h"
#include "KYI_GeometryCollection.generated.h"

/**
 * 
 */
UCLASS()
class ANGRYBIRDVR_API AKYI_GeometryCollection : public AGeometryCollectionActor
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AKYI_GeometryCollection();

//protected:
//	// Called when the game starts or when spawned
//	virtual void BeginPlay() override;
//
//public:
//	// Called every frame
//	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class UGeometryCollectionComponent* geometry;
};
