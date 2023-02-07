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
	//[SetupPlayerInputComponent] �����Լ�
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)override; //�ڡڡڴٸ� ���Ͽ��� �����Լ� ���� �� virtual, override ����ߴµ� ���� �ʿ� ���°ž�? ��?
	void SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent);

public:
	//[EnhancedInputComponent] �������Ʈ
	//Input Action. ������ �׸� �ڡڡڽ��� ���ӿ����� ������ Ʈ���� ���
	UPROPERTY(EditAnyWhere)
	class UInputAction* rightGrip;

public:
	//�÷��̾�
	class ARIM_Player* player;

	//�Ķ���
	class ARIM_BirdBlue* birdBlue;

	//�Ķ��� �������Ʈ Ŭ����
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ARIM_BirdBlue> blueFactory;

public:
	//��ų ���
	//void inputSkill();


		
};
