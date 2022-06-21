import { StyleSheet } from "react-native";

export const styles = StyleSheet.create({
  container: {
    padding: 20,
    paddingHorizontal: 50,
    borderRadius: 100,
    shadowColor: "#000",
    shadowOffset: { width: 0, height: 1 },
    shadowOpacity: 0.8,
    shadowRadius: 2,
    elevation: 5,
  },
  text: {
    textAlign: "center",
    fontSize: 15,
  },
  button: {
    marginTop: 20,
    width: 150,
    height: 50,
    alignSelf: "center",
    justifyContent: "center",
    borderRadius: 100,
  },
  buttonText: {
    textAlign: "center",
    fontSize: 20,
  },
});
