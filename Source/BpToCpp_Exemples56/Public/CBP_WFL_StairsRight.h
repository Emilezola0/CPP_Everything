// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include <Components/TextRenderComponent.h>

#include "Engine/GameEngine.h"
#include "CBP_WFL_StairsRight.generated.h"

UCLASS()
class BPTOCPP_EXEMPLES56_API ACBP_WFL_StairsRight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACBP_WFL_StairsRight();

	UPROPERTY()
	USceneComponent* StairsRoot;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "HISM")
	UHierarchicalInstancedStaticMeshComponent* HISM_Stair;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "RenderText")
	UTextRenderComponent* BpName;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "RenderText")
	UTextRenderComponent* CubeCount;


	virtual void OnConstruction(const FTransform& Transform) override;


	//Variables
	UPROPERTY(EditAnywhere, Category = "Default")
	bool bRenderText;

	UPROPERTY(EditAnywhere, Category = "Default")
	UStaticMesh* SM_Stone;

	UPROPERTY(EditAnywhere, Category = "Default")
	int StonesX;

	UPROPERTY(EditAnywhere, Category = "Default")
	int StonesZ;

	UPROPERTY(EditAnywhere, Category = "Default")
	float StoneZOffset;

	UPROPERTY(BlueprintReadWrite, Category = "Default")
	FVector MeshBounds;

	UPROPERTY(BlueprintReadWrite, Category = "Default")
	float ZValue;

	UPROPERTY(BlueprintReadWrite, Category = "Default")
	float ZValueMax;

	UPROPERTY(BlueprintReadWrite, Category = "Default")
	int CubesTotal;

	UPROPERTY(BlueprintReadWrite, Category = "Default")
	int ZloopIndex = 0.0f;

	UPROPERTY(BlueprintReadWrite, Category = "Default")
	int Collumns;

	UPROPERTY(BlueprintReadWrite, Category = "Default")
	int XLoopIndex;

	UPROPERTY(BlueprintReadWrite, Category = "Default")
	float XValue;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
