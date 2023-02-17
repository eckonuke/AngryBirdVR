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


//EnhancedInput. 입력
void URIM_WidgetPointerComponent::SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent)
{
	//오른손 트리거 ---> 버튼 클릭
	PlayerInputComponent->BindAction(rightTrigger, ETriggerEvent::Started, this, &URIM_WidgetPointerComponent::WidgetClickPressed);
	PlayerInputComponent->BindAction(rightTrigger, ETriggerEvent::Completed, this, &URIM_WidgetPointerComponent::WidgetClickReleased);

	//왼손 트리거 ---> 버튼 클릭
	PlayerInputComponent->BindAction(leftTrigger, ETriggerEvent::Started, this, &URIM_WidgetPointerComponent::WidgetClickPressed);
	PlayerInputComponent->BindAction(leftTrigger, ETriggerEvent::Completed, this, &URIM_WidgetPointerComponent::WidgetClickReleased);


}


//오른손/왼손 트리거. ---> UI 요소에 대한 버튼 Pressed 때 함수
void URIM_WidgetPointerComponent::WidgetClickPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("Widget Pointer ---> Pressed"));

	player->compWidgetPointer_right->PressPointerKey(EKeys::LeftMouseButton); //마우스 왼쪽과 동일하게 처리(Press 처리)
	player->compWidgetPointer_left->PressPointerKey(EKeys::LeftMouseButton); //마우스 왼쪽과 동일하게 처리(Press 처리)
}

//오른손/왼손 트리거. ---> UI 요소에 대한 버튼 Released 때 함수
void URIM_WidgetPointerComponent::WidgetClickReleased()
{
	UE_LOG(LogTemp, Warning, TEXT("Widget Pointer ---> Release"));

	player->compWidgetPointer_right->ReleasePointerKey(EKeys::LeftMouseButton); //마우스 왼쪽과 동일하게 처리(Release 처리)
	player->compWidgetPointer_left->ReleasePointerKey(EKeys::LeftMouseButton); //마우스 왼쪽과 동일하게 처리(Release 처리
}