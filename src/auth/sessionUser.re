open JustgageReasonCookie;

let saveUser = value => Cookie.setString("jsessionid", value);
let getUser = () => Cookie.getAsString("jsessionid");

let isConnected =
  switch (getUser()) {
  | Some(_) => true
  | None => false
  };

let getToken =
  switch (getUser()) {
  | Some(value) => value
  | None => ""
  };