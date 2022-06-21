import React, { useCallback, useEffect, useState } from "react";
import {
  Alert,
  FlatList,
  Image,
  PermissionsAndroid,
  RefreshControl,
  ScrollView,
  Switch,
} from "react-native";
import { BleManager, Device as BLEdevice } from "react-native-ble-plx";
import { Separator } from "../../components/Separator";
import ThemedScrollView from "../../components/StyledScrollView";
import ThemedText from "../../components/ThemedText";
import ThemedView from "../../components/ThemedView";

import { styles } from "./styles";

const wait = (timeout: number) => {
  return new Promise((resolve) => setTimeout(resolve, timeout));
};
interface ConnectBLEscreenProps {
  bluetoothManager: BleManager;
  startNewManager: () => void;
}

export default function ConnectBLEscreen(props: ConnectBLEscreenProps) {
  const { bluetoothManager, startNewManager } = props;
  const [BLEstate, setBLEstate] = useState(false);
  const [list, setList] = useState<BLEdevice[]>([]);
  const [refreshing, setRefreshing] = React.useState(false);

  const onRefresh = React.useCallback(() => {
    setRefreshing(true);
    scanDevices();
    wait(5000).then(() => setRefreshing(false));
  }, []);

  const scanDevices = useCallback(async () => {
    let devices: BLEdevice[] = [];
    setList([]);
    bluetoothManager.startDeviceScan(
      null,
      { allowDuplicates: false },
      (error, device) => {
        if (error) {
          console.log(error);
        } else {
          if (device && device.name) {
            if (devices.includes(device)) {
              return;
            }

            devices.push(device);
            setList(devices);
          }
        }
      }
    );

    setTimeout(() => {
      bluetoothManager.stopDeviceScan();
      devices = [];
    }, 5000);
  }, [bluetoothManager]);
  useEffect(() => {
    (async () => {
      const state = await bluetoothManager.state();
      setBLEstate(state === "PoweredOn");
    })();

    if (BLEstate === true) {
      scanDevices();
    }
  }, []);

  bluetoothManager.onStateChange((state) => {
    setBLEstate(state === "PoweredOn");

    if (state === "PoweredOn") {
      scanDevices();
    }
  });

  return (
    <ThemedView style={styles.container} lightColor="#eee" darkColor="#1f1f1f">
      <Switch
        style={styles.switch}
        trackColor={{ true: "#1f2f1f", false: "#2f3f3f" }}
        thumbColor={BLEstate ? "#090" : "#121"}
        value={BLEstate}
        onChange={async () => {
          if (BLEstate) {
            try {
              await bluetoothManager.disable();
            } catch (error) {
              Alert.alert("Erro", "Não foi possível desligar o Bluetooth", [], {
                cancelable: true,
              });
            }
            startNewManager();
          } else {
            try {
              await bluetoothManager.enable();
            } catch (error) {
              Alert.alert("Erro", "Não foi possível ligar o Bluetooth", [], {
                cancelable: true,
              });
            }
          }
        }}
      />
      <ThemedText style={styles.bluetoothState}>
        Bluetooth {BLEstate ? "Ativado" : "Desativado"}
      </ThemedText>
      <Separator style={{ position: "absolute", top: 45 }} />
      {!BLEstate ? (
        <Image
          style={{
            position: "absolute",
            width: 300,
            height: 300,
          }}
          source={require("../../assets/BLEdisabled.png")}
        />
      ) : (
        <FlatList
          data={list}
          style={styles.list}
          refreshControl={
            <RefreshControl refreshing={refreshing} onRefresh={onRefresh} />
          }
          renderItem={({ item }) => (
            <ThemedView style={styles.item} lightColor="" darkColor="#3d3d3d">
              <ThemedText style={styles.itemText}>{item.localName}</ThemedText>
            </ThemedView>
          )}
          keyExtractor={(item) => item.id}
        />
      )}
    </ThemedView>
  );
}
