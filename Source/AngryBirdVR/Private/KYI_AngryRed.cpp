// Fill out your copyright notice in the Description page of Project Settings.


#include "KYI_AngryRed.h"
#include <Components/SkeletalMeshComponent.h>
#include <Engine/SkeletalMesh.h>
#include "GameFramework/ProjectileMovementComponent.h"
#include <Components/SphereComponent.h>


// Sets default values
AKYI_AngryRed::AKYI_AngryRed()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SetRootComponent(sphereComp);
	sphereComp->SetSphereRadius(20);
	sphereComp->SetSimulatePhysics(true);
	//Skeletal Mesh ����
	skeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Resource/Red/Red.Red'"));
	if (tempMesh.Succeeded())
		skeletalMesh->SetSkeletalMesh(tempMesh.Object);
	skeletalMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	skeletalMesh->SetupAttachment(sphereComp);
	movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	movement->SetUpdatedComponent(sphereComp);
	movement->bShouldBounce = true;
	movement->Bounciness = 0.5f;
}

// Called when the game starts or when spawned
void AKYI_AngryRed::BeginPlay()
{
	Super::BeginPlay();
	sphereComp->OnComponentHit.AddDynamic(this, &AKYI_AngryRed::ComponentHitObject);
	SetLifeSpan(4);
}

// Called every frame
void AKYI_AngryRed::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AKYI_AngryRed::ComponentHitObject(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* actor = Hit.GetActor();
	if (actor) {
		FString name = actor->GetName();
		if (name.Contains("Angry") || name.Contains("Glass") || name.Contains("Wood") || name.Contains("Pig")) {
			actor->Destroy();
		}
	}
}