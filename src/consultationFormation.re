open DecodeLevel;
open DecodeTraining;
let styleInput = ReactDOMRe.Style.make(~paddingLeft="20px");

let url_dev: string = "http://localhost:8080/";

let initialLevel = {
  idLevel: 0,
  grade: "",
  level: 0,
  nbEcts: 0,
  titre: "",
}
type state = DecodeTraining.trainingResponse;


type action =
  | Error(string)
  | Loaded(state);



let component = ReasonReact.reducerComponent("consultationFormation");

let make = _children => {
  let getTraining = self => {
  let payload = Js.Dict.empty();
  Js.Promise.(
    Fetch.fetchWithInit(
      "./public/trainings.json",
      Fetch.RequestInit.make(
        ~method_=Get,
        ~headers=Fetch.HeadersInit.make({"Content-Type": "application/json"}),
        (),
     )
    )
    |> Js.Promise.then_(Fetch.Response.json)
    |> Js.Promise.then_(json => json 
          |> DecodeTraining.decodeResponse
          |> response => response.profile
          |> (result => self.ReasonReact.send(Loaded(result)))
          |> resolve
    )
  )
  |> ignore;
};
{
  ...component,
  initialState: () => {
      idFormation: "",
      name: Some(""),
      description: Some(""),
      admLevel: Some(initialLevel),
      diplomaLevel: initialLevel,
      expertise: Some(""),
      partTime: Some(false),
      logoPath: Some(""),
      link: Some(""),
      duration: "",
      schoolName: "",
      schoolDescription: Some(""),
      schoolPostalcode: "",
      schoolCity: Some(""),
      lowestScore: Some(0),
      highestScore: Some(0),
      averageScore: Some(0.0),
  },
  reducer: (action, state) =>
    switch (action) {
    | Error(string) => ReasonReact.NoUpdate
    | Loaded(result) =>
      ReasonReact.Update({
        idFormation: result.idFormation,
        name: result.name,
        description: result.description,
        admLevel: result.admLevel,
        diplomaLevel: result.diplomaLevel,
        expertise: result.expertise,
        partTime: result.partTime,
        logoPath: result.logoPath,
        link: result.link,
        duration: result.duration,
        schoolName: result.schoolName,
        schoolDescription: result.schoolDescription,
        schoolPostalcode: result.schoolPostalcode,
        schoolCity: result.schoolCity,
        lowestScore: result.lowestScore,
        highestScore: result.highestScore,
        averageScore: result.averageScore,
      })
    },
  didMount: self => getTraining(self),
  render: _self =>
    <div className="card align-middle mx-auto w-50 p-3 text-center">
      <div className="card-header">
        {ReasonReact.string("Consultation d'une formation")}
      </div>
      <div className="card-body">
        <div className="input-group mb-3">
          <label>
          {ReasonReact.string(switch(_self.state.name) {
            |Some(value) => value  
            |None => ""
            })
            }
          </label>
        </div>
        <div className="input-group mb-3">
          <label>{ReasonReact.string(switch(_self.state.description){
            |Some(value) => value  
            |None => ""
            }
          )}          
          </label>
        </div>
        <div className="input-group mb-3">
          <input
            className="form-control"
            type_="text"
            value={switch(_self.state.expertise){
            |Some(value) => value  
            |None => ""
            }}
            placeholder="Niveau d'expertise"
          />
        </div>
        <div className="input-group mb-3">
          <div className="input-group-prepend">
            <span className="input-group-text" id="">
              {ReasonReact.string("Alternance :")}
            </span>
          </div>
          <select className="form-control" id="pet-select">
            <option value="">
              {ReasonReact.string("Choix d'une option")}
            </option>
            <option value={switch(_self.state.partTime){
            |Some(value) => "true"  
            |None => "true"
            }}>
              {ReasonReact.string("Oui")}
            </option>
            <option value={switch(_self.state.partTime){
            |Some(value) => "false"  
            |None => "false"
            }}>
              {ReasonReact.string("Non")}
            </option>
          </select>
        </div>
        <div className="input-group mb-3">
          <div className="input-group-prepend">
            <span className="input-group-text" id="">
              {ReasonReact.string("Photo de la formation :")}
            </span>
          </div>
          <input
            className="styleInput"
            type_="file"
            value={switch(_self.state.logoPath){
            |Some(value) => value  
            |None => ""
            }}
          />
        </div>
        <div className="input-group mb-3">
          <input
            className="form-control"
            type_="text"
            value={switch(_self.state.link){
            |Some(value) => value  
            |None => ""
            }}
            placeholder="lien du site de l'école"
          />
        </div>
        <div className="input-group mb-3">
          <input
            className="form-control"
            type_="text"
            value={_self.state.duration}
            placeholder="Durée de la formation"
          />
        </div>
        <div className="input-group mb-3">
          <input
            className="form-control"
            type_="text"
            value={_self.state.schoolName}
            placeholder="Nom de l'école"
          />
        </div>
        <div className="input-group mb-3">
          <input
            className="form-control"
            type_="text"
            value={switch(_self.state.schoolDescription){
            |Some(value) => value  
            |None => ""
            }}
            placeholder="Description de l'école"
          />
        </div>
        <div className="input-group mb-3">
          <input
            className="form-control"
            type_="text"
            value={_self.state.schoolPostalcode}
            placeholder="Code postale de la ville de l'école"
          />
        </div>
        <div className="input-group mb-3">
          <input
            className="form-control"
            type_="text"
            value={switch(_self.state.schoolCity){
            |Some(value) => value  
            |None => ""
            }}
            placeholder="Nom de la ville de l'école"
          />
        </div>
      </div>
      <label> {ReasonReact.string(switch(_self.state.name){
            |Some(value) => value  
            |None => ""
            })} </label>
      <label> {ReasonReact.string(switch(_self.state.description){
            |Some(value) => value  
            |None => ""
            })} </label>
      <label> {ReasonReact.string(switch(_self.state.partTime){
            |Some(value) => "value " 
            |None => ""
            })} </label>
    </div>,
}
};
