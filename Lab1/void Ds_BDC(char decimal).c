void Ds_BDC(char decimal)
    switch (decimal)

    case 0:

        IO_RA0_SetHigh()//a Encendido
        IO_RA1_SetHigh() //b Encendido
        IO_RA2_SetHigh() //c Encendido
        IO_RA3_SetHigh()//d Encendido
        IO_RA4_SetHigh()//e Encendido
        IO_RA7_SetHigh()//f Encendido
        IO_RA6_SetLow()//g Apagado


    break;

    case 1:

        IO_RA0_SetLow()//a Apagado
        IO_RA1_SetHigh()//b Encendido
        IO_RA2_SetHigh()//c Encendido
        IO_RA3_SetLow()//d Apagado
        IO_RA4_SetLow()//e Apagado
        IO_RA7_SetLow()//f Apagado
        IO_RA6_SetLow()//g Apagado


    break;


    case 2:

        IO_RA0_SetHigh()//a Encendido
        IO_RA1_SetHigh()//b Encendido
        IO_RA2_SetLow()//c Apagado
        IO_RA3_SetHigh())//d Encendido
        IO_RA4_SetHigh()//e Encendido
        IO_RA7_SetLow()//f Apagado
        IO_RA6_SetHigh()//g Encendido


    break;


    case 3:

        IO_RA0_SetHigh()//a Encendido
        IO_RA1_SetHigh()//b Encendido
        IO_RA2_SetHigh()//c Encendido
        IO_RA3_SetHigh()//d Encendido
        IO_RA4_SetLow()//e Apagado
        IO_RA7_SetLow()//f Apagado
        IO_RA6_SetHigh()//g Encendido


    break;



    case 4:

        IO_RA0_SetLow()//a Apagago
        IO_RA1_SetHigh()//b Encendido
        IO_RA2_SetHigh()//c Encendido
        IO_RA3_SetLow()//d Apagado
        IO_RA4_SetLow()//e Apagado
        IO_RA7_SetHigh()//f Encendido
        IO_RA6_SetHigh()//g Encendido


    break;

    case 5:

        IO_RA0_SetHigh()//a Encendido
        IO_RA1_SetLow()//b Apagado
        IO_RA2_SetHigh()//c Encendido
        IO_RA3_SetHigh()//d Encendido
        IO_RA4_SetLow()//e Apagado
        IO_RA7_SetHigh()//f Encendido
        IO_RA6_SetHigh()//g Encendido


    break;


    case 6:

        IO_RA0_SetHigh()//a Encendido
        IO_RA1_SetLow()//b Apagado
        IO_RA2_SetHigh()//c Encendido
        IO_RA3_SetHigh()//d Encendido
        IO_RA4_SetHigh()//e Encendido
        IO_RA7_SetHigh()//f Encendido
        IO_RA6_SetHigh()//g Encendido


    break;


    case 7:

        IO_RA0_SetHigh()//a Encendido
        IO_RA1_SetHigh()//b Encendido
        IO_RA2_SetHigh()//c Encendido
        IO_RA3_SetLow()//d Apagado
        IO_RA4_SetLow()//e Apagado
        IO_RA7_SetLow()//f Apagado
        IO_RA6_SetLow()//g Apagado


    break;


    case 8:

        IO_RA0_SetHigh()//a Encendido
        IO_RA1_SetHigh()//b Encendido
        IO_RA2_SetHigh()//c Encendido
        IO_RA3_SetHigh()//d Encendido
        IO_RA4_SetHigh()//e Encendido
        IO_RA7_SetHigh()//f Encendido
        IO_RA6_SetHigh()//g Encendido


    break;


    case 9:

        IO_RA0_SetHigh()//a Encendido
        IO_RA1_SetHigh()//b Encendido
        IO_RA2_SetHigh()//c Encendido
        IO_RA3_SetHigh()//d Encendido
        IO_RA4_SetLow()//e Apagado
        IO_RA7_SetHigh()//f Encendido
        IO_RA6_SetHigh()//g Encendido


    break;
