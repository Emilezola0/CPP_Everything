// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_SplineStonesPIColor.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values
ACPP_SplineStonesPIColor::ACPP_SplineStonesPIColor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Components Setup
	KarimSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRootComponent"));
	RootComponent = KarimSceneRoot;

	BpName = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Name of the Bp"));
	BpName->SetupAttachment(KarimSceneRoot);

	CubeCount = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Total Cubes"));
	CubeCount->SetupAttachment(KarimSceneRoot);

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("MainSpline"));
	Spline->SetupAttachment(KarimSceneRoot);

	HISM_00 = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("MainHISM"));
	HISM_00->SetupAttachment(KarimSceneRoot);

	//Default Values
	bRenderText = true;
	Stones = 0;
	StoneZOffset = 50.0f;

}

void ACPP_SplineStonesPIColor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	BpName->SetVisibility(bRenderText);
	CubeCount->SetVisibility(bRenderText);
	HISM_00->ClearInstances();
	HISM_00->SetStaticMesh(SM_Stone);
	
	HISM_00->NumCustomDataFloats = 3;
	FLinearColor L_Color = {1.0f, 1.0f, 1.0f, 1.0f};

	if (Stones > 0 && SM_Stone && PICD_Material)
	{
		HISM_00->SetMaterial(0, PICD_Material);
		FVector L_StoneLocation;
		FRotator L_StoneRotation;
		FVector L_StoneScale;
		FTransform L_InstanceTransform;
		int L_InstanceIndex;

		float Length = Spline->GetSplineLength();

		int i = 0;
		for (i = 0; i < Stones; i++) {
			float SplinePart = (Length / (Stones - 1)) * i;

			L_StoneLocation = ((Spline->GetLocationAtDistanceAlongSpline(SplinePart, ESplineCoordinateSpace::World) + FVector(0, 0, StoneZOffset)));
			L_StoneRotation = Spline->GetRotationAtDistanceAlongSpline(SplinePart, ESplineCoordinateSpace::World);
			L_StoneScale = { 1.0f,1.0f,1.0f };
			L_InstanceTransform = UKismetMathLibrary::MakeTransform(L_StoneLocation, L_StoneRotation, L_StoneScale);

			L_InstanceIndex = HISM_00->AddInstance(L_InstanceTransform, true);
			UKismetMathLibrary::LinearColor_SetRandomHue(L_Color);

			HISM_00->SetCustomDataValue(L_InstanceIndex, 0, L_Color.R, false);
			HISM_00->SetCustomDataValue(L_InstanceIndex, 1, L_Color.G, false);
			HISM_00->SetCustomDataValue(L_InstanceIndex, 2, L_Color.B, false);
		}
	}

	FString Str = "Cube Count : ";
	Str.AppendInt(HISM_00->GetInstanceCount());
	CubeCount->SetText(FText::FromString(Str));
}

// Called when the game starts or when spawned
void ACPP_SplineStonesPIColor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_SplineStonesPIColor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

