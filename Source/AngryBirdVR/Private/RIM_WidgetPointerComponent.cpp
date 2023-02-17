// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_WidgetPointerComponent.h"
#include "RIM_Player.h"
#include "EnhancedInputComponent.h"
#include "Components/WidgetInteractionComponent.h"
#include <MotionControllerComponent.h>

// Sets default values for this component's properties
URIM_WidgetPointerComponent::URIM_WidgetPointerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URIM_WidgetPointerComponent::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<ARIM_Player>(GetOwner());
	
}


// Called every frame
void URIM_WidgetPointerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


//EnhancedInput. �Է�
void URIM_WidgetPointerComponent::SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent)
{
	//������ Ʈ���� ---> ��ư Ŭ��
	PlayerInputComponent->BindAction(rightTrigger, ETriggerEvent::Started, this, &URIM_WidgetPointerComponent::WidgetClickPressed);
	PlayerInputComponent->BindAction(rightTrigger, ETriggerEvent::Completed, this, &URIM_WidgetPointerComponent::WidgetClickReleased);

	//�޼� Ʈ���� ---> ��ư Ŭ��
	PlayerInputComponent->BindAction(leftTrigger, ETriggerEvent::Started, this, &URIM_WidgetPointerComponent::WidgetClickPressed);
	PlayerInputComponent->BindAction(leftTrigger, ETriggerEvent::Completed, this, &URIM_WidgetPointerComponent::WidgetClickReleased);


}


//������/�޼� Ʈ����. ---> UI ��ҿ� ���� ��ư Pressed �� �Լ�
void URIM_WidgetPointerComponent::WidgetClickPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("Widget Pointer ---> Pressed"));

	player->compWidgetPointer_right->PressPointerKey(EKeys::LeftMouseButton); //���콺 ���ʰ� �����ϰ� ó��(Press ó��)
	player->compWidgetPointer_left->PressPointerKey(EKeys::LeftMouseButton); //���콺 ���ʰ� �����ϰ� ó��(Press ó��)
}

//������/�޼� Ʈ����. ---> UI ��ҿ� ���� ��ư Released �� �Լ�
void URIM_WidgetPointerComponent::WidgetClickReleased()
{
	UE_LOG(LogTemp, Warning, TEXT("Widget Pointer ---> Release"));

	player->compWidgetPointer_right->ReleasePointerKey(EKeys::LeftMouseButton); //���콺 ���ʰ� �����ϰ� ó��(Release ó��)
	player->compWidgetPointer_left->ReleasePointerKey(EKeys::LeftMouseButton); //���콺 ���ʰ� �����ϰ� ó��(Release ó��
}