// Fill out your copyright notice in the Description page of Project Settings.


#include "KYI_Wood.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>

// Sets default values
AKYI_Wood::AKYI_Wood()
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
void AKYI_Wood::BeginPlay()
{
	Super::BeginPlay();
	boxComp->OnComponentHit.AddDynamic(this, &AKYI_Wood::ComponentHitObject);
}

// Called every frame
void AKYI_Wood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKYI_Wood::ComponentHitObject(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	if (Hit.GetActor()) {
		FString name = Hit.GetActor()->GetName();
		if (name.Contains("Red") || name.Contains("Wood") || name.Contains("Yellow") || name.Contains("Black")) {
			Die();
		}
	}
}

void AKYI_Wood::Die(){
	if (life > 0) {
		life--;
	}
	else {
		Destroy();
	}
}