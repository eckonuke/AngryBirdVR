// Fill out your copyright notice in the Description page of Project Settings.


#include "KYI_AngryRed.h"
#include <Components/SkeletalMeshComponent.h>
#include <Engine/SkeletalMesh.h>

// Sets default values
AKYI_AngryRed::AKYI_AngryRed()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	skeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Resource/Red/Red.Red'"));
	if (tempMesh.Succeeded())
		skeletalMesh->SetSkeletalMesh(tempMesh.Object);
}

// Called when the game starts or when spawned
void AKYI_AngryRed::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKYI_AngryRed::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

