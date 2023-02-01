// Fill out your copyright notice in the Description page of Project Settings.


#include "KYI_SlingShot.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AKYI_SlingShot::AKYI_SlingShot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AKYI_SlingShot::BeginPlay()
{
	Super::BeginPlay();
	//GameplayStatics::PredictProjectilePath();
}

// Called every frame
void AKYI_SlingShot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

