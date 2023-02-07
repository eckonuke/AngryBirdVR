// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BirdSkill.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ANGRYBIRDVR_API UBirdSkill : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBirdSkill();

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
	//Input Action. 오른손 그립 ★★★실제 게임에서는 오른손 트리거 사용
	UPROPERTY(EditAnyWhere)
	class UInputAction* rightGrip;

public:
	//플레이어
	class ARIM_Player* player;

	//파란새
	class ARIM_BirdBlue* birdBlue;

	//파란새 블루프린트 클래스
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ARIM_BirdBlue> blueFactory;

public:
	//스킬 사용
	//void inputSkill();


		
};
