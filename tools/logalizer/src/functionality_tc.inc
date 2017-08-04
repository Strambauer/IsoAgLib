const char* ddis[] = {
"DDI 0 - not valid!!!!",
"Setpoint Volume Per Area Application Rate",
"Actual Volume Per Area Application Rate",
"Default Volume Per Area Application Rate",
"Minimum Volume Per Area Application Rate",
"Maximum Volume Per Area Application Rate",
"Setpoint Mass Per Area Application Rate",
"Actual Mass Per Area Application Rate",
"Default Mass Per Area Application Rate",
"Minimum Mass Per Area Application Rate",
"Maximum Mass Per Area Application Rate",
"Setpoint Count Per Area Application Rate",
"Actual Count Per Area Application Rate",
"Default Count Per Area Application Rate",
"Minimum CountPer Area Application Rate",
"Maximum Count Per Area Application Rate",
"Setpoint Spacing Application Rate",
"Actual Spacing Application Rate",
"Default Spacing Application Rate",
"Minimum Spacing Application Rate",
"Maximum Spacing Application Rate",
"Setpoint Volume Per Volume Application Rate",
"Actual Volume Per Volume Application Rate",
"Default Volume Per Volume Application Rate",
"Minimum Volume Per Volume Application Rate",
"Maximum Volume Per Volume Application Rate",
"Setpoint Mass Per Mass Application Rate",
"Actual Mass Per Mass Application Rate",
"Default Mass Per MassA pplication Rate",
"Minimum Mass Per Mass Application Rate",
"MaximumMass Per Mass Application Rate",
"Setpoint Volume Per Mass Application Rate",
"Actual Volume Per Mass Application Rate",
"Default Volume Per Mass Application Rate",
"Minimum Volume Per Mass Application Rate",
"Maximum Volume Per Mass Application Rate",
"Setpoint Volume Per Time Application Rate",
"Actual Volume Per Time Application Rate",
"Default Volume Per Time Application Rate",
"Minimum Volume Per Time Application Rate",
"Maximum Volume Per Time Application Rate",
"Setpoint Mass Per Time Application Rate",
"Actual Mass Per Time Application Rate",
"Default Mass Per Time Application Rate",
"Minimum Mass Per Time Application Rate",
"Maximum Mass Per Time Application Rate",
"Setpoint Count Per Time Application Rate",
"Actual Count Per Time Application Rate",
"Default Count Per Time Application Rate",
"Minimum Count Per Time Application Rate",
"Maximum Count Per Time Application Rate",
"Setpoint Tillage Depth",
"Actual Tillage Depth",
"Default Tillage Depth",
"Minimum Tillage Depth",
"Maximum Tillage Depth",
"Setpoint Seeding Depth",
"Actual Seeding Depth",
"Default Seeding Depth",
"Minimum Seeding Depth",
"Maximum Seeding Depth",
"Setpoint Working Height",
"Actual Working Height",
"Default Working Height",
"Minimum Working Height",
"Maximum Working Height",
"Setpoint Working Width",
"Actual Working Width",
"Default Working Width",
"Minimum Working Width",
"Maximum Working Width",
"Setpoint Volume Content",
"Actual Volume Content",
"Maximum Volume Content",
"Setpoint Mass Content",
"Actual Mass Content",
"Maximum Mass Content",
"Setpoint Count Content",
"Actual Count Content",
"Maximum Count Content",
"Application Total Volume",
"Application Total Mass",
"Application Total Count",
"Volume Per Area Yield",
"Mass Per Area Yield",
"Count Per Area Yield",
"Volume Per Time Yield",
"Mass Per Time Yield",
"Count Per Time Yield",
"Yield Total Volume",
"Yield Total Mass",
"Yield Total Count",
"Volume Per Area Crop Loss",
"Mass Per Area Crop Loss",
"Count Per Area Crop Loss",
"Volume Per Time Crop Loss",
"Mass Per Time Crop Loss",
"Count Per Time Crop Loss",
"Percentage Crop Loss",
"Crop Moisture",
"Crop Contamination",
"Setpoint Bale Width",
"Actual Bale Width",
"Default Bale Width",
"Minimum Bale Width",
"Maximum Bale Width",
"Setpoint Bale Height",
"ActualBaleHeight",
"Default Bale Height",
"Minimum Bale Height",
"Maximum Bale Height",
"Setpoint Bale Size",
"Actual Bale Size",
"Default Bale Size",
"Minimum Bale Size",
"Maximum Bale Size",
"Total Area",
"Effective Total Distance",
"Ineffective Total Distance",
"Effective Total Time",
"Ineffective Total Time",
"Product Density Mass Per Volume",
"Product Density Mass PerCount",
"Product Density Volume Per Count",
"Auxiliary Valve Scaling Extend",
"Auxiliary Valve Scaling Retract",
"Auxiliary Valve Ramp Extend Up",
"Auxiliary Valve Ramp Extend Down",
"Auxiliary Valve Ramp Retract Up",
"Auxiliary Valve Ramp Retract Down",
"Auxiliary Valve Float Threshold",
"Auxiliary Valve Progressivity Extend",
"Auxiliary Valve Progressivity Retract",
"Auxiliary Valve Invert Ports",
"Device Element Offset X",
"Device Element Offset Y",
"Device Element Offset Z",
"Device Volume Capacity",
"Device Mass Capacity",
"Device Count Capacity",
"Percentage Application Rate Setpoint",
"Actual Work State",
"Physical Setpoint Time Latency",
"Physical Actual Value Time Latency",
"Yaw Angle",
"Roll Angle",
"Pitch Angle",
"Log Count",
"Total Fuel Consumption",
"Instantaneous Fuel Consumption per Time",
"Instantaneous Fuel Consumption per Area",
"Instantaneous Area Per Time Capacity",
"DDI 152 - not valid!!!!!",
"Actual Normalized Difference Vegetative Index (NDVI)",
"Physical Object Length",
"Physical Object Width",
"Physical Object Height",
"Connector Type",
"Prescription Control State",
"Number of Sub-Units per Section",
"Section Control State",
"Actual Condensed Work State (1-16)",
"Actual Condensed Work State (17-32)",
"Actual Condensed Work State (33-48)",
"Actual Condensed Work State (49-64)",
"Actual Condensed Work State (65-80)",
"Actual Condensed Work State (81-96)",
"Actual Condensed Work State (97-112)",
"Actual Condensed Work State (113-128)",
"Actual Condensed Work State (129-144)",
"Actual Condensed Work State (145-160)",
"Actual Condensed Work State (161-176)",
"Actual Condensed Work State (177-192)",
"Actual Condensed Work State (193-208)",
"Actual Condensed Work State (209-224)",
"Actual Condensed Work State (225-240)",
"Actual Condensed Work State (241-256)",
"Actual length of cut",
"Element Type Instance",
"Actual Cultural Practice",
"Device Reference Point (DRP) to Ground distance",
"Dry Mass Per Area Yield",
"Dry Mass Per Time Yield",
"Yield Total Dry Mass",
"Reference Moisture For Dry Mass",
"Seed Cotton Mass Per Area Yield",
"Lint Cotton Mass Per Area Yield",
"Seed Cotton Mass Per Time Yield",
"Lint Cotton Mass Per Time Yield",
"Yield Total Seed Cotton Mass",
"Yield Total Lint Cotton Mass",
"Lint Turnout Percentage ",
"Ambient temperature",
"Setpoint Product Pressure",
"Actual Product Pressure",
"Minimum Product Pressure",
"Maximum Product Pressure",
"Setpoint Pump Output Pressure",
"Actual Pump Output Pressure",
"Minimum Pump Output Pressure",
"Maximum Pump Output Pressure",
"Setpoint Tank Agitation Pressure",
"Actual Tank Agitation Pressure",
"Minimum Tank Agitation Pressure",
"Maximum Tank Agitation Pressure",
"SC Turn On Time",
"SC Turn Off Time",
"Wind speed",
"Wind direction",
"Air Humidity",
"Sky conditions",
"Last Bale Flakes per Bale",
"Last Bale Average Moisture",
"Last Bale Average Strokes per Flake",
"Lifetime Bale Count",
"Lifetime Working Hours",
"Actual Bale Hydraulic Pressure",
"Last Bale Average Hydraulic Pressure",
"Setpoint Bale Compression Plunger Load",
"Actual Bale Compression Plunger Load",
"Last Bale Average Bale Compression Plunger Load",
"Last Bale Applied Preservative",
"Last Bale Tag Number",
"Last Bale Mass",
"Delta T",
"Setpoint Working Length",
"Actual Working Length",
"Minimum Working Length",
"Maximum Working Length",
"Actual Net Weight",
"Net Weight State",
"Setpoint Net Weight",
"Actual Gross Weight",
"Gross Weight State",
"Minimum Gross Weight",
"Maximum Gross Weight",
"Threshing Engagement Total Time",
"Actual Header Working Height Status",
"Actual Header Rotational Speed Status",
"Yield Hold Status",
"Actual (Un)Loading System Status",
"Crop Temperature",
"Setpoint Sieve Clearance",
"Actual Sieve Clearance",
"Minimum Sieve Clearance",
"Maximum Sieve Clearance",
"Setpoint Chaffer Clearance",
"Actual Chaffer Clearance",
"Minimum Chaffer Clearance",
"Maximum Chaffer Clearance",
"Setpoint Concave Clearance",
"Actual Concave Clearance",
"Minimum Concave Clearance",
"Maximum Concave Clearance",
"Setpoint Separation Fan Rotational Speed",
"Actual Separation Fan Rotational Speed",
"Minimum Separation Fan Rotational Speed",
"Maximum Separation Fan Rotational Speed",
"Hydraulic Oil Temperature",
"Yield Lag Ignore Time",
"Yield Lead Ignore Time",
"Average Yield Mass Per Time",
"Average Crop Moisture",
"Average Yield Mass Per Area",
"Connector Pivot X-Offset",
"Remaining Area",
"Lifetime Application Total Mass",
"Lifetime Application Total Count",
"Lifetime Yield Total Volume",
"Lifetime Yield Total Mass",
"Lifetime Yield Total Count",
"Lifetime Total Area",
"Lifetime Total Distance",
"Lifetime Ineffective Total Distance",
"Lifetime Effective Total Time",
"Lifetime Ineffective Total Time",
"Lifetime Fuel Consumption",
"Lifetime Average Fuel Consumption per Time",
"Lifetime Average Fuel Consumption per Area",
"Lifetime Yield Total Dry Mass",
"Lifetime Yield Total Seed Cotton Mass",
"Lifetime Yield Total Lint Cotton Mass",
"Lifetime Threshing Engagement Total Time",
"Precut Total Count",
"Uncut Total Count",
"Lifetime Precut Total Count",
"Lifetime Uncut Total Count",
"DDI 287 - not valid!!!!!",
"DDI 298 - not valid!!!!!",
"Setpoint Work State",
"Setpoint Condensed Work State (1-16)",
"Setpoint Condensed Work State (17-32)",
"Setpoint Condensed Work State (33-48)",
"Setpoint Condensed Work State (49-64)",
"Setpoint Condensed Work State (65-80)",
"Setpoint Condensed Work State (81-96)",
"Setpoint Condensed Work State (97-112)",
"Setpoint Condensed Work State (113-128)",
"Setpoint Condensed Work State (129-144)",
"Setpoint Condensed Work State (145-160)",
"Setpoint Condensed Work State (161-176)",
"Setpoint Condensed Work State (177-192)",
"Setpoint Condensed Work State (193-208)",
"Setpoint Condensed Work State (209-224)",
"Setpoint Condensed Work State (225-240)",
"Setpoint Condensed Work State (241-256)",
"True Rotation Point  X-Offset ",
"True Rotation Point Y-Offset",
"Actual Percentage Application Rate",
"Minimum Percentage Application Rate",
"Maximum Percentage Application Rate",
"Relative Yield Potential",
"Minimum Relative Yield Potential",
"Maximum Relative Yield Potential"
};

std::string
decodeTechnicalCapabilities( uint8_t cmd )
{
  std::ostringstream out;

  switch( cmd )
  {
  case 0x0: out << "Version Request"; break;
  case 0x1: out << "Version"; break;
  default:  out << "Not specified Request/Answer!!!"; break;
  }

  return out.str();
}

std::string
decodeDevDescTransMgmt( uint8_t cmd )
{
  std::ostringstream out;

  switch( cmd )
  {
  case 0x0: out << "Structure Label Request"; break;
  case 0x1: out << "Structure Label"; break;
  case 0x2: out << "Localization Label Request"; break;
  case 0x3: out << "Localization Label"; break;
  case 0x4: out << "Request Object-pool Transfer"; break;
  case 0x5: out << "Request Object-pool Transfer Response"; break;
  case 0x6: out << "Object-pool Transfer"; break;
  case 0x7: out << "Object-pool Transfer Response"; break;
  case 0x8: out << "Object-pool Activate"; break;
  case 0x9: out << "Object-pool Activate Response"; break;
  case 0xA: out << "Object-pool Delete"; break;
  case 0xB: out << "Object-pool Delete Reponse"; break;
  case 0xC: out << "Change Designator"; break;
  case 0xD: out << "Change Designator Response"; break;
  default:  out << "Not specified Request/Answer!!!"; break;
  }

  return out.str();
}

std::string
interpreteProcessData( PtrDataFrame_t at_ptrFrame )
{
  if (at_ptrFrame->dataSize() < 8)
    return "*** ILLEGAL - THIS PGN *MUST* HAVE AT LEAST 8 DATABYTES ***";

  std::ostringstream out;

  if (at_ptrFrame->dataSize() > 8)
  { // can only be device description upload
  }
  else
  {
    bool valueAndMeasurementCommand = false;

    switch (at_ptrFrame->dataOctet(0) & 0x0F)
    {
    case 0x00: out << "Command Technical Capabilities " << decodeTechnicalCapabilities( at_ptrFrame->dataOctet(0) >> 4 ); break;
    case 0x01: out << "Command Device Descriptor " << decodeDevDescTransMgmt( at_ptrFrame->dataOctet(0) >> 4 ); break;
    case 0x02: out << "Command Request Value  "; valueAndMeasurementCommand = true; break;
    case 0x03: out << "Command Value          "; valueAndMeasurementCommand = true; break;
    case 0x04: out << "Command Measur. Time   "; valueAndMeasurementCommand = true; break;
    case 0x05: out << "Command Measur. Dist.  "; valueAndMeasurementCommand = true; break;
    case 0x06: out << "Command Measur. Min.   "; valueAndMeasurementCommand = true; break;
    case 0x07: out << "Command Measur. Max.   "; valueAndMeasurementCommand = true; break;
    case 0x08: out << "Command Measur. Change "; valueAndMeasurementCommand = true; break;
    case 0x09: out << "Command Peer Control Assignment"; break;
    case 0x0A: out << "Command Set Value and Acknowledge"; break;
    case 0x0D: out << "Message Process Data Acknowledge (PDACK)"; break;
    case 0x0E: out << "Message Task Controller Status"; break;
    case 0x0F: out << "Message Working Set Task"; break;
    default:   out << "RESERVED."; break;
    }

    if( valueAndMeasurementCommand )
    {
      uint16_t element = (uint16_t(at_ptrFrame->dataOctet(0) >> 4)) | uint16_t(uint16_t(at_ptrFrame->dataOctet(1)) << 4);
      uint32_t ddi = uint16_t(at_ptrFrame->dataOctet(2)) | (uint16_t(at_ptrFrame->dataOctet(3)) << 8);
      int32_t value = int32_t( uint32_t(at_ptrFrame->dataOctet(4)) | uint32_t(at_ptrFrame->dataOctet(5))<<8 | uint32_t(at_ptrFrame->dataOctet(6))<<16 | uint32_t(at_ptrFrame->dataOctet(7))<<24 );

      out << "E=" << std::setw(4) << std::dec << element << " DDI=";
      if( ddi >= 0xdfff )
        out << "$" << std::setw(4) << std::hex << ddi << std::dec;
      else
        out << std::setw(5) << std::dec << ddi;
      out << " => " << std::setw(11) << std::left << value;
      
      if( ddi < (sizeof(ddis) / sizeof(const char*)) )
        out << " (" << ddis[ ddi ] << ")";
      else if( ddi == 0xdffe )
        out << " (PGN Based Data)";
      else if( ddi == 0xdfff )
        out << " (Request Default Process Data)";
      else if( ddi == 0xffff )
        out << " (Reserved)";
      else
        out << " (Proprietary DDI)";
    }

    if( gs_main.mb_storeDdop && ( at_ptrFrame->data()[0] == 0x81 ) ) {
      ddopStore( at_ptrFrame->sourceAddress() );
    }
  }

  return out.str();
}