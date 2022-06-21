import { StyleSheet } from "react-native";

export const styles = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: "center",
    justifyContent: "center",
  },
  switch: {
    position: "absolute",
    top: 10,
    right: 10,
  },
  bluetoothState: {
    position: "absolute",
    top: 10,
    fontSize: 20,
    textAlign: "center",
  },
  list: {
    flex: 1,
    width: "85%",
    alignSelf: "center",
    marginTop: 60,
  },
  item: {
    flexDirection: "row",
    justifyContent: "space-between",
    alignItems: "center",
    borderRadius: 15,
    marginTop: 10,
    padding: 10,
  },
  itemText: {
    fontSize: 20,
    fontWeight: "bold",
  },
});
