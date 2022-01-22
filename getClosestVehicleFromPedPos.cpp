// Using Script Hook V SDK 
// dev-c.com/gtav/scripthookv/
 
// Gets the closest vehicle depending on ped pos with the function getClosestVehicleFromPedPos.

bool doesEntityExistsAndIsNotNull(Entity entity){
    return (entity != NULL && ENTITY::DOES_ENTITY_EXIST(entity));
}
 
float getDistanceBetweenEntities(Entity entity1, Entity entity2){
    Vector3 entity1Coords = ENTITY::GET_ENTITY_COORDS(entity1, true);
    Vector3 entity2Coords = ENTITY::GET_ENTITY_COORDS(entity2, true);
    return GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(entity1Coords.x, entity1Coords.y, entity1Coords.z, entity2Coords.x, entity2Coords.y, entity2Coords.z, 1);
}
 
float getDistanceToGround(Entity entity){
    Vector3 entityCoords = ENTITY::GET_ENTITY_COORDS(entity, true);
    float groundZ = 0;
    GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(entityCoords.x, entityCoords.y, entityCoords.z, &groundZ, 0);
    return GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(entityCoords.x, entityCoords.y, entityCoords.z, entityCoords.x, entityCoords.y, groundZ, 1);
}
 
Hash getModelHash(Vehicle veh){
    return ENTITY::GET_ENTITY_MODEL(veh);
}
 
bool isVehicleDrivable(Vehicle veh){
    if (VEHICLE::IS_VEHICLE_DRIVEABLE(veh, false) && 
        (VEHICLE::IS_THIS_MODEL_A_CAR(getModelHash(veh)) ||
        VEHICLE::IS_THIS_MODEL_A_BIKE(getModelHash(veh)) ||
        VEHICLE::IS_THIS_MODEL_A_QUADBIKE(getModelHash(veh)) ||
        //VEHICLE::IS_THIS_MODEL_A_TRAIN(getModel(veh)) || // use if you like to
        VEHICLE::IS_THIS_MODEL_A_HELI(getModelHash(veh)) ||
        //VEHICLE::_IS_THIS_MODEL_A_SUBMERSIBLE(getModel(veh)) || // doesn't seem to work
        VEHICLE::IS_THIS_MODEL_A_PLANE(getModelHash(veh)) ||
        VEHICLE::IS_THIS_MODEL_A_BOAT(getModelHash(veh)) ||
        VEHICLE::IS_THIS_MODEL_A_BICYCLE(getModelHash(veh)))){
        return true;
    }
 
    return false;
}
 
Vehicle getClosestVehicleFromPedPos(Ped ped, int maxDistance, int maxHeight, bool canReturnVehicleInside){
    Vehicle veh = NULL;
    float smallestDistance = (float)maxDistance;
    const int ARR_SIZE = 1024;
    Vehicle vehs[ARR_SIZE];
    int count = worldGetAllVehicles(vehs, ARR_SIZE);
 
    if (vehs != NULL)
    {
        for (int i = 0; i < count; i++)
        {
            if (doesEntityExistsAndIsNotNull(vehs[i]) && (canReturnVehicleInside || PED::IS_PED_IN_VEHICLE(ped, vehs[i], false) == false))
            {
                float distance = getDistanceBetweenEntities(ped, vehs[i]);
                float height = getDistanceToGround(vehs[i]);
                if (distance <= smallestDistance && height <= maxHeight && height >= 0 && isVehicleDrivable(vehs[i]))
                {
                    smallestDistance = distance;
                    veh = vehs[i];
                }
            }
        }
    }
 
    return veh;
}