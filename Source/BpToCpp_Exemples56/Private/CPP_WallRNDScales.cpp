// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_WallRNDScales.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values
ACPP_WallRNDScales::ACPP_WallRNDScales()
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

	HISM_00 = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("MainHISM"));
	HISM_00->SetupAttachment(KarimSceneRoot);

	//Default Values
	bRenderText = true;
	Stones_X = 5;
	Stones_Z = 5;
	StoneZOffset = 50.0f;
	MinScale = 0.25f;
	MaxScale = 1.0f;
}

void ACPP_WallRNDScales::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	BpName->SetVisibility(bRenderText);
	CubeCount->SetVisibility(bRenderText);
	HISM_00->ClearInstances();
	HISM_00->SetStaticMesh(SM_Stone);

	if (Stones_X > 0 && Stones_Z > 0 && SM_Stone)
	{
		FVector Bound = SM_Stone->GetBoundingBox().Max - SM_Stone->GetBoundingBox().Min;
		float StoneSizeX = Bound.X;
		float StoneSizeZ = Bound.Z;

		FVector L_StoneLocation_X;
		FVector L_StoneLocation_Z;
		FRotator L_StoneRotation;
		FVector L_StoneScale;
		FTransform L_InstanceTransform;

		L_StoneRotation = { 0,0,0 };
		L_StoneScale = { 1,1,1 };

		int i = 0;
		int j = 0;

		for (i = 0; i < Stones_X; i++) {

			L_StoneLocation_X = (i * UKismetMathLibrary::MakeVector(StoneSizeX, 0.0f, 0.0f)) + UKismetMathLibrary::MakeVector(0.0f, 0.0f, StoneZOffset);

			for (j = 0; j < Stones_Z; j++) {
				L_StoneLocation_Z = (j * UKismetMathLibrary::MakeVector(0.0f, 0.0f, StoneSizeZ));
				L_InstanceTransform = (UKismetMathLibrary::MakeTransform((L_StoneLocation_X + L_StoneLocation_Z), L_StoneRotation, L_StoneScale));
				HISM_00->AddInstance(L_InstanceTransform, false);
			}
		}
	}

	FString Str = "Cube Count : ";
	Str.AppendInt(HISM_00->GetInstanceCount());
	CubeCount->SetText(FText::FromString(Str));
}

// Called when the game starts or when spawned
void ACPP_WallRNDScales::BeginPlay()
{
	Super::BeginPlay();
	
	if (HISM_00->GetInstanceCount() > 0) {

		FVector Bound = SM_Stone->GetBoundingBox().Max - SM_Stone->GetBoundingBox().Min;
		float StoneSizeY = Bound.Y;
		float RndScaleValue = 0;

		FTransform L_InstanceTransform = FTransform();
		FVector NewLocation;
		FRotator NewRotation;
		FVector NewScale;
		FTransform L_NewInstanceTransform = FTransform();

		int i = 0;
		for (i = 0; i < HISM_00->GetInstanceCount(); i++) {

			RndScaleValue = UKismetMathLibrary::RandomFloatInRange(MinScale, MaxScale);
			HISM_00->GetInstanceTransform(i, L_InstanceTransform, false);

			if (bAlignStones) {
				NewLocation = L_InstanceTransform.GetLocation() + UKismetMathLibrary::MakeVector(0, (StoneSizeY / 2 * RndScaleValue), 0);
			}
			else {
				NewLocation = L_InstanceTransform.GetLocation() + UKismetMathLibrary::MakeVector(0, (RndScaleValue), 0);
			}

			NewRotation = FRotator(L_InstanceTransform.GetRotation());
			NewScale = UKismetMathLibrary::MakeVector(1, RndScaleValue, 1);

			L_NewInstanceTransform = UKismetMathLibrary::MakeTransform(NewLocation, NewRotation, NewScale);

			HISM_00->UpdateInstanceTransform(i, L_NewInstanceTransform, false, false, false);
		}
	}
}

// Called every frame
void ACPP_WallRNDScales::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

