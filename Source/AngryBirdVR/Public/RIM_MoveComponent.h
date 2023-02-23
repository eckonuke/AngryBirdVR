// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RIM_MoveComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ANGRYBIRDVR_API URIM_MoveComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URIM_MoveComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	//[SetupPlayerInputComponent] 가상함수
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)override; //★★★다른 파일에서 가상함수 만들 때 virtual, override 사용했는데 여긴 필요 없는거야? 왜?
	void SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent);

public:
	//[EnhancedInputComponent] 블루프린트
	//Input Action. 오른손 트리거
	UPROPERTY(EditAnyWhere)
	class UInputAction* rightTrigger;

	

 public:
	//[컨트롤러 버튼 함수]
	//이동 라인(곡선) 그리기
	void DrawMoveLine();
	//순간 이동. 즉시 좌표 변경
	void Teleport();

	//오른손 트리거 ---> 이동
	void rightTriggerShowLine();
	void rightTriggerHideLine();

	//카메라 페이드
	void TeleportFade();

	//테스트
// 	void OnTriggerR();
// 	void OffTriggerR();


public:
	//플레이어
	class ARIM_Player* player;
	
	//이동 라인을 그리는 시간 간격
	float lineTimeInterval = 0.1f; //▶필요 시 조정

	//현재 위치에서 이동할 위치 사이의...
	int32 lineTimeSegment = 50; //▶필요 시 조정

	//이동할 위치
	TArray<FVector> lineLocation; 

	//파워
	UPROPERTY(EditAnywhere)
	float power = 10000; //▶필요 시 조정

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ARIM_MoveLocation* position;

	//이동 라인이 안 보인다
	bool bIsShowLine = false; //true 일 때 매 프레임마다 그려라
	bool isTeleport = true;;

private:
	class UWorld* currentWorld;
};
