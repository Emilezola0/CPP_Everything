// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/SceneComponent.h"
#include <Components/TextRenderComponent.h>
#include "Components/SplineComponent.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Engine/StaticMesh.h"

//GEngine AddOnScreenDebugMessage. Print function.
#include "Engine/GameEngine.h"

//ACHTUNG!! #include "X.generated.h" must ALWAYS be the last one
#include "CPP_SplineStones.generated.h"

UCLASS()
class BPTOCPP_EXEMPLES56_API ACPP_SplineStones : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_SplineStones();

	//OnConstruction is called to re-build the ConstructionScript Code when a change is made. (Its replicates the natural behaviour of a blueprint)
	virtual void OnConstruction(const FTransform& Transform) override;

	//Components Setup
	UPROPERTY()
	USceneComponent* KarimSceneRoot;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "RenderText")
	UTextRenderComponent* BpName;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "RenderText")
	UTextRenderComponent* CubeCount;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Components")
	USplineComponent* Spline;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Components")
	UHierarchicalInstancedStaticMeshComponent* HISM_00;

	//Variables
	UPROPERTY(EditAnywhere, Category = "Default")
	bool bRenderText;

	UPROPERTY(EditAnywhere, Category = "Default")
	UStaticMesh* SM_Stone;

	UPROPERTY(EditAnywhere, Category = "Default")
	int Stones;

	UPROPERTY(EditAnywhere, Category = "Default")
	float StoneZOffset;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
