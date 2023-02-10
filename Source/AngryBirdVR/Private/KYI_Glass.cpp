// Fill out your copyright notice in the Description page of Project Settings.


#include "KYI_Glass.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>

// Sets default values
AKYI_Glass::AKYI_Glass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Comp"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(50));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Comp"));
	meshComp->SetupAttachment(boxComp);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (tempMesh.Succeeded())
		meshComp->SetStaticMesh(tempMesh.Object);
}

// Called when the game starts or when spawned
void AKYI_Glass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKYI_Glass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

