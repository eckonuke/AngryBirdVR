// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RIM_WidgetPointerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ANGRYBIRDVR_API URIM_WidgetPointerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URIM_WidgetPointerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	//EnhancedInput. 입력
	void SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent);

public:
	//Input Action. 오른손 트리거 ---> 버튼 클릭
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UInputAction* rightTrigger;

	//Input Action. 왼손 트리거 ---> 버튼 클릭
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UInputAction* leftTrigger;

public:
	UPROPERTY()
	class ARIM_Player* player;


public:
	//Input Action. 오른손/왼손 트리거. ---> UI 요소에 대한 버튼 Pressed 때 함수
	void WidgetClickPressed();
	
	//Input Action. 오른손/왼손 트리거. ---> UI 요소에 대한 버튼 Released 때 함수
	void WidgetClickReleased();
};
