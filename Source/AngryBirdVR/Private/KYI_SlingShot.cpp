// Fill out your copyright notice in the Description page of Project Settings.


#include "KYI_SlingShot.h"
#include "Kismet/GameplayStatics.h"
#include <Components/BoxComponent.h>

// Sets default values
AKYI_SlingShot::AKYI_SlingShot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	compBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SetRootComponent(compBox);
	compMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (tempMesh.Succeeded())
		compMesh->SetStaticMesh(tempMesh.Object);
	compMesh->SetupAttachment(compBox);
	
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

