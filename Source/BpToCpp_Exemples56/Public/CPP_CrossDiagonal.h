// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// Components
#include "Components/SceneComponent.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"

// Text
#include <Components/TextRenderComponent.h>

// Engine
#include "Engine/StaticMesh.h"

// LAST
#include "CPP_CrossDiagonal.generated.h"

UCLASS()
class BPTOCPP_EXEMPLES56_API ACPP_CrossDiagonal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_CrossDiagonal();

	// ON CONSTRUCTIOn
	virtual void OnConstruction(const FTransform& Transform) override;

	// --------------------
	// Components
	// --------------------
	UPROPERTY()
	USceneComponent* SceneRoot;

	UPROPERTY()
	UTextRenderComponent* BpName;

	UPROPERTY()
	UTextRenderComponent* CubeCount;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
	UHierarchicalInstancedStaticMeshComponent* HISM_00;

	// --------------------
	// Variables
	// --------------------
	
	UPROPERTY(EditAnywhere, Category = "Default")
	UStaticMesh* SM_Stone;

	UPROPERTY(EditAnywhere, Category = "Default")
	int Stones_XY;

	UPROPERTY(EditAnywhere, Category = "Default")
	float StoneZ_Offset;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// FUNCTIONS
	FVector GetMeshHalfSize();

};
