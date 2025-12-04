// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_SplineStonesRNDScales.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values
ACPP_SplineStonesRNDScales::ACPP_SplineStonesRNDScales()
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

	bRenderText = true;
	Stones = 0;
	MinScale = 0.65f;
	MaxScale = 2.0f;
	StoneZOffset = 50;
	Seed = 0;
}

void ACPP_SplineStonesRNDScales::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	BpName->SetVisibility(bRenderText);
	CubeCount->SetVisibility(bRenderText);
	HISM_00->ClearInstances();
	HISM_00->SetStaticMesh(SM_Stone);


	Stream.Initialize(Seed);

	if (Stones > 0)
	{
		FVector L_StoneLocation;
		FRotator L_StoneRotation;
		FVector L_StoneScale;
		FTransform L_InstanceTransform;

		float Length = Spline->GetSplineLength();

		int i = 0;
		for (i = 0; i < (Stones); i++) {

			float SplinePart = i * (Length / (Stones - 1));

			L_StoneLocation = ((Spline->GetLocationAtDistanceAlongSpline(SplinePart, ESplineCoordinateSpace::World) + FVector(0, 0, StoneZOffset)));
			L_StoneRotation = UKismetMathLibrary::ComposeRotators((Spline->GetRotationAtDistanceAlongSpline(SplinePart, ESplineCoordinateSpace::World)), UKismetMathLibrary::RandomRotatorFromStream(Stream, true));
			L_StoneScale = UKismetMathLibrary::MakeVector(UKismetMathLibrary::RandomFloatInRangeFromStream(Stream, MinScale, MaxScale), UKismetMathLibrary::RandomFloatInRangeFromStream(Stream, MinScale, MaxScale), UKismetMathLibrary::RandomFloatInRangeFromStream(Stream, MinScale, MaxScale));


			L_InstanceTransform = UKismetMathLibrary::MakeTransform(L_StoneLocation, L_StoneRotation, L_StoneScale);
			HISM_00->AddInstance(L_InstanceTransform, true);
		}
	}

	FString Str = "Cube Count : ";
	Str.AppendInt(HISM_00->GetInstanceCount());
	CubeCount->SetText(FText::FromString(Str));
}

// Called when the game starts or when spawned
void ACPP_SplineStonesRNDScales::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_SplineStonesRNDScales::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

