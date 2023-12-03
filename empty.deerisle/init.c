void main()
{
    CreateHive();
    GetHive().InitOffline();
    int year, month, day, hour, minute;
    GetGame().GetWorld().GetDate( year, month, day, hour, minute );

    //Change here the dates for whatever months you desire
    if ( month < 12 )
    {
        year  = 2030;
        month = 12;
        day   = 30;
        
        GetGame().GetWorld().SetDate( year, month, day, hour, minute );
    }
} 

class CustomMission: MissionServer
{
    void SetRandomHealth(EntityAI itemEnt)
    {
        if ( itemEnt )
        {
            int rndHlt = Math.RandomInt(55,100);
            itemEnt.SetHealth("","",rndHlt);
        }
    }

    override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
    {
        Entity playerEnt;
        playerEnt = GetGame().CreatePlayer(identity, characterName, pos, 0, "NONE");//Creates random player
        Class.CastTo(m_player, playerEnt);

        GetGame().SelectPlayer(identity, m_player);

        return m_player;
    }

    override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
    {
        EntityAI itemTop;
        EntityAI itemEnt;
        ItemBase itemBs;

        float rand;

        itemTop = player.FindAttachmentBySlotName("Body");

        if ( itemTop )
        {
            itemEnt = itemTop.GetInventory().CreateInInventory("Rag");

            if ( Class.CastTo(itemBs, itemEnt ) )
                itemBs.SetQuantity(4);

            SetRandomHealth(itemEnt);

            string chemlightArray[] = { "Chemlight_White", "Chemlight_Yellow", "Chemlight_Green", "Chemlight_Red" };
            int rndIndex = Math.RandomInt(0, 4);
            itemEnt = itemTop.GetInventory().CreateInInventory(chemlightArray[rndIndex]);
            
            SetRandomHealth(itemEnt);

            rand = Math.RandomFloatInclusive(0.0, 1.0);
            if ( rand < 0.35 )
                itemEnt = player.GetInventory().CreateInInventory("Apple");
            else if ( rand > 0.65 )
                itemEnt = player.GetInventory().CreateInInventory("Pear");
            else
                itemEnt = player.GetInventory().CreateInInventory("Plum");

            SetRandomHealth(itemEnt);
            
            itemEnt = player.GetInventory().CreateInInventory("Rag");
        }
    }
};

Mission CreateCustomMission(string path)
{
    return new CustomMission();
}