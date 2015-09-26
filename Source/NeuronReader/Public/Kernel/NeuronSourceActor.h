#pragma once


/** Neuron bone info
*/
struct FNeuronBoneInfo
{
public:

	/** Bone Position
	*/
	FVector Position;

	/** Bone Rotation
	*/
	FRotator Rotation;

};


/** Source Actor
*/
class FNeuronSourceActor
{
public:
	FNeuronSourceActor(FNeuronSource* InSource, int32 InActorID);
	~FNeuronSourceActor();
public:

	/** On actor suspend
	*/
	FNeuronSourceActorSignature OnSuspend;
	/** On actor resume
	*/
	FNeuronSourceActorSignature OnResume;

private:

	/** Source
	*/
	FNeuronSource* Source;

	/** Actor ID
	*/
	int32 ActorID;

	/** ��һ������֡��ʱ��
	*/
	FDateTime LastFrameTime;

	/** ��ǰ�Ǽ����ݳ�1
	*/
	TArray<FNeuronBoneInfo> BoneBuffer1;
	/** ��ǰ�Ǽ����ݳ�2
	*/
	TArray<FNeuronBoneInfo> BoneBuffer2;

	/** ��ǰʹ�õ�Buffer */
	TArray<FNeuronBoneInfo>* UsingBuffer;
	/** ��ǰдֵ��Buffer */
	TArray<FNeuronBoneInfo>* ShadowBuffer;

	/** Critical section
	*/
	FCriticalSection CriticalSection;

public:
	FORCEINLINE FNeuronSource* GetSource() const {
		return Source;
	}
	FORCEINLINE int32 GetActorID() const {
		return ActorID;
	}

	/** Get bone data of last frame.
	*/
	void GetBoneData(ENeuronBones::Type InBoneType, FVector& OutPosition, FRotator& OutRotation);

private:

	/** enter suspend state
	*/
	void _Suspend();

	/** resume state
	*/
	void _Resume();

	/** Called when host-source is destroying.
	*/
	void _PostSourceDestroy();
	friend class FNeuronSource;

	/** called when got NeuronAxis's frame data.
	*	only called by _NeuronDataReaderCallbacks
	*/
	void _OnReceiveFrameData(float* InData, int32 InDataCount, bool InDisplacement);
	friend class _NeuronDataReaderCallbacks;

};