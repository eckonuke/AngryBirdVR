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
	//[SetupPlayerInputComponent] �����Լ�
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)override; //�ڡڡڴٸ� ���Ͽ��� �����Լ� ���� �� virtual, override ����ߴµ� ���� �ʿ� ���°ž�? ��?
	void SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent);

public:
	//[EnhancedInputComponent] �������Ʈ
	//Input Action. ������ Ʈ����
	UPROPERTY(EditAnyWhere)
	class UInputAction* rightTrigger;

	

 public:
	//[��Ʈ�ѷ� ��ư �Լ�]
	//�̵� ����(�) �׸���
	void DrawMoveLine();
	//���� �̵�. ��� ��ǥ ����
	void Teleport();

	//������ Ʈ���� ---> �̵�
	void rightTriggerShowLine();
	void rightTriggerHideLine();

	//ī�޶� ���̵�
	void TeleportFade();

	//�׽�Ʈ
// 	void OnTriggerR();
// 	void OffTriggerR();


public:
	//�÷��̾�
	class ARIM_Player* player;
	
	//�̵� ������ �׸��� �ð� ����
	float lineTimeInterval = 0.1f; //���ʿ� �� ����

	//���� ��ġ���� �̵��� ��ġ ������...
	int32 lineTimeSegment = 50; //���ʿ� �� ����

	//�̵��� ��ġ
	TArray<FVector> lineLocation; 

	//�Ŀ�
	UPROPERTY(EditAnywhere)
	float power = 10000; //���ʿ� �� ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ARIM_MoveLocation* position;

	//�̵� ������ �� ���δ�
	bool bIsShowLine = false; //true �� �� �� �����Ӹ��� �׷���
	bool isTeleport = true;;

private:
	class UWorld* currentWorld;
};
