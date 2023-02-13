// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_MoveLocation.h"
#include <Components/BoxComponent.h>

// Sets default values
ARIM_MoveLocation::ARIM_MoveLocation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	compCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	compCollision->SetupAttachment(RootComponent);
	compCollision->SetBoxExtent(FVector(50.0f)); //▶추후 변경


}

// Called when the game starts or when spawned
void ARIM_MoveLocation::BeginPlay()
{
	Super::BeginPlay();
	
	compCollision->OnComponentBeginOverlap.AddDynamic(this, &ARIM_MoveLocation::ComponentBeginOverlapMove);
}

// Called every frame
void ARIM_MoveLocation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ARIM_MoveLocation::ComponentBeginOverlapMove(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

