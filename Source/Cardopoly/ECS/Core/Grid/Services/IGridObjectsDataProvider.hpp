class IGridObjectsDataProvider
{
public:
	virtual TArray<FIntVector> GetLocalPositions(uint32 id) = 0;
	
	virtual ~IGridObjectsDataProvider() = default;
};