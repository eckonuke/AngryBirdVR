// Fill out your copyright notice in the Description page of Project Settings.


#include "PredictionObject.h"
#include <Components/StaticMeshComponent.h>
#include <Kismet/KismetSystemLibrary.h>

// Sets default values
APredictionObject::APredictionObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (tempMesh.Succeeded()) {
		mesh->SetStaticMesh(tempMesh.Object);
	}
	mesh->SetRelativeScale3D(FVector(0.01f));
	mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mesh->SetCollisionObjectType(ECC_GameTraceChannel3);
	ConstructorHelpers::FObjectFinder<UMaterial> tempMat(TEXT("/Script/Engine.Material'/Game/BluePrints/Mat_PredObj.Mat_PredObj'"));
	if (tempMat.Succeeded()) {
		mesh->SetMaterial(0, tempMat.Object);
	}
}

// Called when the game starts or when spawned
void APredictionObject::BeginPlay() {
	Super::BeginPlay();
	SetLifeSpan(0.5);
}

// Called every frame
void APredictionObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

