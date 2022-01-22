// Using Script Hook V SDK 
// dev-c.com/gtav/scripthookv/
 
// From player pos, gets the closest ped, vehicle, object or pickup depending on function used.
 
const int ARR_SIZE = 1024;
 
Ped getPlayerPed()
{
    return PLAYER::PLAYER_PED_ID();
}
 
bool doesEntityExistsAndIsNotNull(Entity entity)
{
    return (entity != NULL && ENTITY::DOES_ENTITY_EXIST(entity));
}
 
float getDistanceBetweenVectors(Vector3 vector1, Vector3 vector2)
{
    return SYSTEM::VDIST(vector1.x, vector1.y, vector1.z, vector2.x, vector2.y, vector2.z);
}
 
Entity getEntityClosestToCoords(Entity entities[], int count, Vector3 coords, float maxDistance)
{
    float shortestDistance = maxDistance; // start value
    Entity closestEntity = NULL;
 
    if (entities != NULL)
    {
        for (int i = 0; i < count; i++)
        {
            if (doesEntityExistsAndIsNotNull(entities[i]))
            {
                Vector3 entCoords = ENTITY::GET_ENTITY_COORDS(entities[i], true);
                float distanceFound = getDistanceBetweenVectors(coords, entCoords);
                if (distanceFound <= shortestDistance)
                {
                    shortestDistance = distanceFound;
                    closestEntity = entities[i];
                }
            }
        }
    }
    return closestEntity;
}
 
Ped getPedClosestToCoords(Vector3 coords, float maxDistance)
{
    Ped peds[ARR_SIZE];
    int count = worldGetAllPeds(peds, ARR_SIZE);
    return getEntityClosestToCoords(peds, count, coords, maxDistance);
}
 
Object getObjectClosestToCoords(Vector3 coords, float maxDistance)
{
    Object objects[ARR_SIZE];
    int count = worldGetAllObjects(objects, ARR_SIZE);
    return getEntityClosestToCoords(objects, count, coords, maxDistance);
}
 
Vehicle getVehicleClosestToCoords(Vector3 coords, float maxDistance)
{
    Vehicle vehicles[ARR_SIZE];
    int count = worldGetAllVehicles(vehicles, ARR_SIZE);
    return getEntityClosestToCoords(vehicles, count, coords, maxDistance);
}
 
Pickup getPickupClosestToCoords(Vector3 coords, float maxDistance)
{
    Pickup pickups[ARR_SIZE];
    int count = worldGetAllPickups(pickups, ARR_SIZE);
    return getEntityClosestToCoords(pickups, count, coords, maxDistance);
}
 
// Example of usage: Getting the closest vehicle from player's coords and make it explode.
void getClosestEntityDemo()
{
    if (doesEntityExistsAndIsNotNull(getPlayerPed()))
    {
        Vector3 playerCoords = ENTITY::GET_ENTITY_COORDS(getPlayerPed(), true);
        Vehicle closestVeh = getVehicleClosestToCoords(playerCoords, 100); // Distance in meters
        if (doesEntityExistsAndIsNotNull(closestVeh))
        {
            VEHICLE::EXPLODE_VEHICLE(closestVeh, true, false);
            //VEHICLE::DELETE_VEHICLE(&closestVeh);
            //VEHICLE::SET_VEHICLE_COLOURS(closestVeh, 0, 0);
        }
    }
}